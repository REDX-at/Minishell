/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exe_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/14 02:39:02 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_built_in(t_cmd *cmd, int fd[][2], t_table *table, int k)
{
	if (cmd->next)
		close(fd[k][1]);
	if (ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd, table);
	else if (ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(cmd, table);
	else if (ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd, table);
	else if (ft_strcmp(cmd->cmd, "env"))
		ft_env(table, cmd);
	else if (ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd, table);
	else if (ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd, table);
	else if (ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd, table);
}

void close_file_descriptor(int fd[][2], int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	creat_pipe(t_table *table, int fd[][2], int k)
{
	while (k < table->count_cmd)
	{
		if (pipe(fd[k]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		k++;
	}
}

void	heredoc(t_cmd *cmd, int red)
{
	int	fd[2];
	char	*line;
	char	**the_buffer;
	int		i;

	i = 0;
	(void)cmd;
	(void)red;
	the_buffer = (char **)malloc(sizeof(char *) * 100);
	pipe(fd);
	int	flag = 0;
	int	is_here = 0;
	while (1)
	{
		line = readline("> ");
		if ((line == NULL || ft_strncmp(line, cmd->file[0], ft_strlen(cmd->file[0])) == 0))
		{
			flag = 1;
			if (cmd->cmd)
			{
				if (ft_strncmp(cmd->cmd, "cat", 3) == 0)
				{
					the_buffer[i] = NULL;
					if (line == NULL)
					{
						line = ft_strdup("> ");
						i = 0;
						the_buffer[i] = ft_strjoin(line, the_buffer[i]);
						i++;
						while (the_buffer[i])
						{
							ft_putstr_fd(the_buffer[i], fd[1]);
							ft_putstr_fd("\n", fd[1]);
							i++;
						}
					}
					is_here++;
					ft_putstr2d_fd(the_buffer, 1);
					printf("is_here = %d\n", is_here);
					if (is_here != 1)
					{
						ft_putstr_fd("\n", 1);
						ft_putstr_fd("hello\n", 1);
					}
				}
			}
			close(fd[1]);
			break ;
		}
		if (flag == 0)
		{
			the_buffer[i] = ft_strdup(line);
			i++;
		}
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	into_child(t_cmd *cmd, int fd[][2], t_table *table, int k)
{
	if (k > 0)
		dup2(fd[k][0], 0);
	if (cmd->next)
		dup2(fd[k + 1][1], 1);
	close_file_descriptor(fd, k);
	int red = 0;
	if (cmd->redir)
	{
		while (cmd->redir[red])
		{
			if (ft_strncmp(cmd->redir[red], "<<", 2) == 0)
				heredoc(cmd, red);
			red++;
		}
	}
	if (cmd->is_builtin)
		execute_built_in(cmd, fd, table, k);
	else if (ft_strcmp(cmd->cmd, "clear"))
		ft_putstr_fd(CLEAR, 1);
	else
		execute_cmd(cmd, fd, cmd->argv, k, table);
	exit(EXIT_SUCCESS);
}

void	wait_all_pid(t_table *table, pid_t pid[], int k)
{
	int	status;

	status = 0;
	while (k < table->count_cmd)
	{
		waitpid(pid[k], &status, 0);
		k++;
	}
	table->exit_status = (WEXITSTATUS(status));
}

void	execute_for_cmd(t_cmd *cmd, t_table *table)
{
	int	k;
	int	fd[table->count_cmd][2];
	pid_t	pid[table->count_cmd];

	k = 0;
	creat_pipe(table, fd, k);
	while (cmd)
	{
		int red = 0;
		int	flag = 0;
		if (cmd->redir)
		{
			while (cmd->redir[red])
			{
				if (ft_strncmp(cmd->redir[red], "<<", 2) == 0)
					flag = 1;
				red++;
			}
		}
		if (cmd->pipe || !cmd->is_builtin || flag)
		{
			pid[k] = fork();
			if (pid[k] == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid[k] == 0)
				into_child(cmd, fd, table, k);
		}
		else
		{
			if (cmd->is_builtin)
				execute_built_in(cmd, fd, table, k);
			else if (ft_strcmp(cmd->cmd, "clear"))
				ft_putstr_fd(CLEAR, 1);
			else
				execute_cmd(cmd, fd, cmd->argv, k, table);
		}
		k++;
		cmd = cmd->next;
	}
	close_file_descriptor(fd, k);
	k = 0;
	wait_all_pid(table, pid, k);
}
