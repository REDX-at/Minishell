/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/12 18:43:07 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**utils_declare_x(t_cmd *cmd, t_table *table, int i)
{
	int		check;
	char	*tmp_argv;
	char	**new_env;
	char	**split;

	split = ft_split(cmd->argv[i], '=');
	split[0] = ft_strjoin("declare -x ", split[0]);
	check = check_if_exist(split[0], table->declare_x, 2);
	if (check != -1)
	{
		if (ft_strchr(cmd->argv[i], '=') != 0)
		{
			tmp_argv = ft_strjoin("declare -x ", cmd->argv[i]);
			table->declare_x[check] = ft_strdup(tmp_argv);
		}
	}
	else
	{
		tmp_argv = ft_strjoin("declare -x ", cmd->argv[i]);
		new_env = ft_add_env2(table->declare_x, tmp_argv);
		sort_double_pointer_2(new_env, ft_strlen_2d(new_env));
		table->declare_x = new_env;
	}
	return (table->declare_x);
}

void	export_declare_x(t_table *table, t_cmd *cmd)
{
	int		i;
	char	**new_env;
	int		test;
	int		valid;

	valid = 0;
	test = 0;
	if (ft_strlen_2d(cmd->argv) > 2)
		new_env = (char **)malloc(sizeof(char *)
				* (ft_strlen_2d(table->env) + ft_strlen_2d(cmd->argv)));
	i = 0;
	while (cmd->argv[++i])
	{
		test = is_alpha_num(cmd->argv[i]);
		if (test == -1 && check_if_valid(cmd->argv[i]))
			test = 1;
		if (ft_strncmp(cmd->argv[i], "_=", 2) != 0 && test != -1)
		{
			if (ft_strchr(cmd->argv[i], '+')
				&& check_if_valid(cmd->argv[i]) == 1)
				the_plus_for_declare_x(cmd, i, table);
			else
				table->declare_x = utils_declare_x(cmd, table, i);
		}
	}
}

char	*get_the_argv_before_equal(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '=')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	the_plus_for_declare_x(t_cmd *cmd, int i, t_table *table)
{
	int		check;
	char	*tmp;
	char	*tmp_2;
	char	*tmp_3;
	char	**split;

	tmp_3 = malloc(sizeof(char) * 255);
	tmp_2 = malloc(sizeof(char) * 255);
	tmp = malloc(sizeof(char) * 255);
	cmd->argv[i] = ft_strjoin("declare -x ", cmd->argv[i]);
	table->j = ft_strlen_until_equal(cmd->argv[i]) + 1;
	tmp_3 = copy_the_str(cmd->argv[i], &table->j, 1);
	tmp = copy_the_str_without_plus(cmd->argv[i]);
	split = ft_split(tmp, '=');
	check = check_if_exist(split[0], table->declare_x, 2);
	table->i = i;
	table->check = check;
	utils_plus_declare_x(cmd, tmp, tmp_2, tmp_3);
}

void	the_plus(t_cmd *cmd, int i, t_table *table)
{
	int		check;
	char	*tmp;
	char	*tmp_2;
	char	*tmp_3;

	tmp_3 = malloc(sizeof(char) * 255);
	tmp_2 = malloc(sizeof(char) * 255);
	tmp = malloc(sizeof(char) * 255);
	table->j = ft_strlen_until_equal(cmd->argv[i]) + 1;
	tmp_3 = copy_the_str(cmd->argv[i], &table->j, 1);
	tmp = copy_the_str_without_plus(cmd->argv[i]);
	check = check_if_exist(tmp, table->env, 1);
	table->i = i;
	table->check = check;
	utils_plus(cmd, tmp, tmp_2, tmp_3);
}
