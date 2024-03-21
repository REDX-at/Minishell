/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:14:53 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/20 01:17:12 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	for_herdoc(t_cmd *cmd, int *fd, char *line, int red)
{
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			free(line);
			continue ;
		}
		if (ft_strncmp(line, cmd->file[red], ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
}

int	heredoc(t_cmd *cmd, int red)
{
	int		fd[2];
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	pipe(fd);
	for_herdoc(cmd, fd, line, red);
	close(fd[1]);
	return (fd[0]);
}
