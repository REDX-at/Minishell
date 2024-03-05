/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:51:03 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/05 21:49:44 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// creat shild with pipe and use execve
void    execute_cmd(t_cmd *cmd, int fd[][2], char **argv, int k)
{
	execve(cmd->cmd, argv, NULL);
	if (check_access(cmd->cmd, cmd) == 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else
	{
		if (cmd->next)
			close(fd[k][0]);
		close(fd[k][1]);
		int	i;

		i = 0;
		while (cmd->redir)
		{
			if (cmd->redir[i] != NULL)
			{
				if (ft_strncmp(cmd->redir[i], ">>", 2) == 0)
					redir_out_append(cmd, i);
				else if (ft_strncmp(cmd->redir[i], ">", 1) == 0)
					redir_out(cmd, i);
				else if (ft_strncmp(cmd->redir[i], "<", 1) == 0)
					redir_in(cmd, i);
			}
			if (cmd->redir[i + 1] == NULL)
			{
				if(execve(cmd->path, argv, NULL) == -1)
					perror("execve");
			}
			i++;
		}
		exit(EXIT_FAILURE);
	}
}