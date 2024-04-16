/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:59:17 by aitaouss          #+#    #+#             */
/*   Updated: 2024/04/16 23:12:50 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	into_child(t_cmd *cmd, int **fd, t_table *table, int k)
{
	handle_redir(cmd, table, k, fd);
	close_file_descriptor(fd, k);
	if (cmd->is_builtin)
		execute_built_in(cmd, fd, table, k);
	else
		execute_cmd(cmd, fd, k, table);
	table->exit_status = 0;
	exit(EXIT_SUCCESS);
}

int	check_the_redir(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "<<", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	inside_loop_2(int k, t_cmd *cmd, int **fd, pid_t pid[])
{
	extern int	g_status;

	if (g_status == 1)
		return ;
	else
		g_status = 2;
	pid[k] = fork();
	if (pid[k] == -1)
	{
		perror("fork");
		cmd->table->exit_status = 1;
		exit(1);
	}
	if (pid[k] == 0)
		into_child(cmd, fd, cmd->table, k);
	else
	{
		close(fd[k][1]);
		if (cmd->redir)
		{
			if (check_the_redir(cmd->redir))
				waitpid(pid[k], NULL, 0);
		}
	}
}

void	loop_child(t_cmd *cmd, int **fd, pid_t pid[])
{
	int			k;

	k = 0;
	while (cmd)
	{
		if (cmd->pipe || !cmd->is_builtin)
			inside_loop_2(k, cmd, fd, pid);
		k++;
		cmd = cmd->next;
	}
}
