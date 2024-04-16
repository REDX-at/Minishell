/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:50:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/31 17:13:23 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utils_plus(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3)
{
	int		j;

	j = -1;
	while (cmd->argv[cmd->table->i][++j])
	{
		if (cmd->argv[cmd->table->i][j] == '+')
		{
			if (cmd->argv[cmd->table->i][j + 1]
				&& cmd->argv[cmd->table->i][j + 1] == '=')
			{
				if (cmd->table->check != -1)
				{
					cmd->table->s = 0;
					tmp_2 = copy_the_str(cmd->table->env[cmd->table->check], &cmd->table->s, 0);
					tmp_2 = ft_strjoin(tmp_2, tmp_3);
					tmp = get_the_argv_before_equal(tmp);
					tmp = ft_strjoin(tmp, tmp_2);
					cmd->table->env[cmd->table->check] = tmp;
				}
				else
					cmd->table->env = ft_add_env2(cmd->table->env, tmp);
			}
		}
	}
}

void	utils_plus_declare_x(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3)
{
	int		j;

	j = -1;
	while (cmd->argv[cmd->table->i][++j])
	{
		if (cmd->argv[cmd->table->i][j] == '+')
		{
			if (cmd->argv[cmd->table->i][j + 1]
				&& cmd->argv[cmd->table->i][j + 1] == '=')
			{
				if (cmd->table->check != -1)
				{
					cmd->table->s = 0;
					tmp_2 = copy_the_str(cmd->table->declare_x[cmd->table->check], &cmd->table->s, 0);
					tmp_2 = ft_strjoin(tmp_2, tmp_3);
					tmp = get_the_argv_before_equal(tmp);
					tmp = ft_strjoin(tmp, tmp_2);
					cmd->table->declare_x[cmd->table->check] = tmp;
				}
				else
					cmd->table->declare_x
						= ft_add_env2(cmd->table->declare_x, tmp);
			}
		}
	}
}

char	*copy_the_str_without_plus(char *str)
{
	char	*tmp;
	int		i;
	int		s;

	s = 0;
	i = 0;
	tmp = malloc(sizeof(char) * 255);
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '+')
		{
			tmp[s] = str[i];
			s++;
		}
		i++;
	}
	tmp[s] = '\0';
	return (tmp);
}
