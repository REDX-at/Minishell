/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:09:13 by aitaouss          #+#    #+#             */
/*   Updated: 2024/04/12 17:10:25 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_with_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_cd(t_cmd *cmd, t_table *table)
{
	char	*path;

	if (search_for_home(table) == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return ;
	}
	if (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 1)
		path = get_env_pro("HOME", table);
	else
		path = cmd->argv[1];
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		print_with_fd(path, 2);
	}
	else
	{
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: permission denied: ", 2);
			print_with_fd(path, 2);
		}
	}
	change_pwd(table);
}

void	for_env(t_table *table, int *signe)
{
	int	i;

	i = -1;
	if (table->red == 1)
	{
		while (table->env[++i])
		{
			if (ft_strncmp(table->env[i], "PATH=", 5) != 0
				&& ft_strncmp(table->env[i], "SHELL=", 5) != 0)
				print_with_fd(table->env[i], 1);
		}
		*signe = -1;
		return ;
	}
}

void	ft_env(t_table *table)
{
	int		i;
	int		fd;
	char	**splited;

	i = -1;
	fd = 0;
	for_env(table, &fd);
	if (fd == -1)
		return ;
	if ((search_for_path(table) != -1))
	{
		splited = ft_split(table->env[search_for_path(table)] + 5, ':');
		while (splited[++i])
		{
			if (ft_strncmp(splited[i], "/usr/bin", 8) == 0)
				fd = 1;
		}
	}
	if ((search_for_path(table) == -1 || fd == 0))
	{
		ft_putstr_fd("msh: env: No such file or directory\n", 2);
		table->exit_status = 127;
		return ;
	}
	ft_putstr2d_fd(table->env, 1);
}
