/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:27:59 by aitaouss          #+#    #+#             */
/*   Updated: 2024/04/12 17:15:47 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		i++;
	}
	if (cmd->echo_new_line == 0)
		ft_putstr_fd("\n", 1);
}

void	for_change_pwd(t_table *table, char **tmp, char **tmp2, char **oldpwd)
{
	int	i;

	i = -1;
	if (!table->flag_old)
	{
		table->flag_old = 1;
		table->env = ft_add_env2(table->env, "OLDPWD=");
	}
	while (table->env[++i])
	{
		if (ft_strncmp(table->env[i], "PWD=", 4) == 0)
		{
			*tmp = ft_strdup(table->env[i]);
			*tmp2 = getcwd(NULL, 0);
			table->env[i] = ft_strjoin("PWD=", *tmp2);
			free(*tmp2);
			free(*tmp);
		}
		if (ft_strncmp(table->env[i], "OLDPWD=", 7) == 0)
		{
			*oldpwd = table->pwd_env;
			table->env[i] = ft_strjoin("OLDPWD=", *oldpwd);
		}
	}
}

void	change_pwd(t_table *table)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*oldpwd;

	i = 0;
	for_change_pwd(table, &tmp, &tmp2, &oldpwd);
	i = 0;
	while (table->declare_x[i])
	{
		if (ft_strncmp(table->declare_x[i], "declare -x PWD=", 15) == 0)
		{
			tmp = ft_strdup(table->declare_x[i]);
			tmp2 = getcwd(NULL, 0);
			table->declare_x[i] = ft_strjoin("declare -x PWD=", tmp2);
			free(tmp2);
			free(tmp);
		}
		if (ft_strncmp(table->declare_x[i], "declare -x OLDPWD", 17) == 0)
			table->declare_x[i]
				= ft_strjoin("declare -x OLDPWD=", table->pwd_env);
		i++;
	}
	table->pwd_env = getcwd(NULL, 0);
}

int	search_for_home(t_table *table)
{
	int	i;

	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], "HOME=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_pro(char *str, t_table *table)
{
	int		i;
	char	*tmp;

	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], str, ft_strlen(str)) == 0)
		{
			tmp = ft_strdup(table->env[i] + (ft_strlen(str) + 1));
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
