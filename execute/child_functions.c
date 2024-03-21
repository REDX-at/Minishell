/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:59:17 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/21 01:25:13 by aitaouss         ###   ########.fr       */
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

void	loop_child(t_cmd *cmd, int **fd, t_table *table, pid_t pid[])
{
	int	k;

	k = 0;
	while (cmd)
	{
		if (cmd->pipe || !cmd->is_builtin)
		{
			pid[k] = fork();
			if (pid[k] == -1)
			{
				perror("fork");
				table->exit_status = 1;
				exit(1);
			}
			if (pid[k] == 0)
				into_child(cmd, fd, table, k);
			else
			{
				close(fd[k][1]);
				if (cmd->redir)
				{
					if (ft_strncmp(cmd->redir[0], "<<", 2) == 0)
						waitpid(pid[k], NULL, 0);
				}
			}
		}
		k++;
		cmd = cmd->next;
	}
}
