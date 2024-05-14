/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:50:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/14 23:06:42 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utils_plus(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3)
{
	// int		j;
	char	*leak;

	// j = 0;
	// while (cmd->argv[++j])
	// {
		if (cmd->table->check != -1)
		{
			cmd->table->s = 0;
			tmp_2 = copy_the_str(cmd->table->env[cmd->table->check], &cmd->table->s, 0);
			leak = ft_strdup(tmp_2);
			free(tmp_2);
			tmp_2 = ft_strjoin(leak, tmp_3);
			free(leak);
			leak = ft_strdup(tmp);
			free(tmp);
			tmp = get_the_argv_before_equal(leak);
			free(leak);
			leak = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strjoin(leak, tmp_2);
			free(leak);
			free(tmp_2);
			free(cmd->table->env[cmd->table->check]);
			cmd->table->env[cmd->table->check] = ft_strdup(tmp);
			free(tmp);
			free(tmp_3);
		}
		else
		{
			cmd->table->env = ft_add_env2(cmd->table->env, tmp);
			free(tmp);
			free(tmp_3);
		}
	// }
}

void	utils_plus_declare_x(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3)
{
	// int		j;
	char	*leak;

	// j = 0;
	// while (cmd->argv[++j])
	// {
		if (cmd->table->check != -1)
		{
			cmd->table->s = 0;
			tmp_2 = copy_the_str_after_equal(cmd->table->declare_x[cmd->table->check]);
			leak = ft_strdup(tmp_2);
			free(tmp_2);
			tmp_2 = ft_strjoin(leak, tmp_3);
			free(leak);
			leak = ft_strdup(tmp);
			free(tmp);
			tmp = get_the_argv_before_equal(leak);
			free(leak);
			leak = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strjoin(leak, tmp_2);
			free(leak);
			free(tmp_2);
			free(cmd->table->declare_x[cmd->table->check]);
			cmd->table->declare_x[cmd->table->check] = ft_strdup(tmp);
			free(tmp);
			free(tmp_3);
		}
		else
		{
			cmd->table->declare_x
				= ft_add_env2(cmd->table->declare_x, tmp);
			free(tmp);
			free(tmp_3);
		}
	// }
}

char	*copy_the_str_without_plus(char *str)
{
	char	*tmp;
	int		i;
	int		s;
	int		flag;

	flag = 0;
	s = 0;
	i = -1;
	tmp = (char *)malloc(sizeof(char) * 255);
	if (!tmp)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '+' && flag == 0)
		{
			i++;
			flag = 1;
		}
		tmp[s] = str[i];
		s++;
	}
	tmp[s] = '\0';
	return (tmp);
}
