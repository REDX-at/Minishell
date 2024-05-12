/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:33:36 by aitaouss          #+#    #+#             */
/*   Updated: 2024/04/18 23:39:04 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*freee(char **string, int index)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		free(string[i]);
		string[i] = NULL;
		i++;
	}
	free(string);
	string = NULL;
	return (NULL);
}

// ft_strcmp function
int	ft_strcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	if (!str || !str2)
		return (0);
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	if (str[i] != str2[i])
		return (0);
	return (1);
}

int	search_for_path(t_table *table)
{
	int	i;

	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	for_acces(t_table *table, t_cmd *cmd, char ***splited)
{
	char	*env;

	if (table->red == -1)
	{
		*splited[0] = ft_strdup("/bin");
		*splited[1] = ft_strdup("/usr/bin");
		*splited[2] = NULL;
	}
	if (search_for_path(table) != -1)
	{
		env = table->env[search_for_path(table)];
		env = ft_strdup(env + 5);
		*splited = ft_split(env, ':');
	}
	if (search_for_path(table) == -1 && table->red == -1)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": No such files or directory for acces\n", 2);
		table->exit_status = 127;
		exit(127);
	}
}

// a function to check the access of the path
int	check_access(char *command, t_cmd *cmd, t_table *table)
{
	char	**splited;
	int		i;
	int		flag;
	char	*new_path;
	char	*new_path2;

	splited = NULL;
	flag = 0;
	i = 0;
	for_acces(table, cmd, &splited);
	while (splited[i])
	{
		new_path = ft_strjoin(splited[i], "/");
		new_path2 = ft_strjoin(new_path, command);
		if (access(new_path2, F_OK) == 0 && access(new_path2, X_OK) == 0)
		{
			flag = 1;
			cmd->path = new_path2;
			break ;
		}
		free(new_path);
		free(new_path2);
		i++;
	}
	free_2d(splited);
	if (flag)
		return (1);
	return (0);
}
