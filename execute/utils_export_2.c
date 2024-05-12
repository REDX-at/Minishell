/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:58:06 by aitaouss          #+#    #+#             */
/*   Updated: 2024/04/25 16:05:51 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quotes_to_string(char *str)
{
	int		len;
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len + 3));
	while (str[++i] && str[i] != '=')
	{
		tmp[j] = str[i];
		j++;
	}
	tmp[j++] = '=';
	tmp[j++] = '"';
	while (str[++i])
	{
		tmp[j] = str[i];
		j++;
	}
	tmp[j] = '"';
	j++;
	tmp[j] = '\0';
	return (tmp);
}

void	after_export(t_cmd *cmd, t_table *table, int check)
{
	int		i;
	int		alnum;

	alnum = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		alnum = is_alpha_num(cmd->argv[i]);
		if (ft_strncmp(cmd->argv[i], "_=", 2) != 0)
		{
			if (cmd->argv[i][0] == '=' || (!ft_isalpha(cmd->argv[i][0]))
				|| check_if_there_is_space(cmd->argv[i]) == -1 || alnum == -1)
			{
				if (!check_if_valid(cmd->argv[i]) || cmd->argv[i][0] == '+')
				{
					ft_putstr_fd("export : not a valid identifier\n", 2);
					table->flag = 1;
					table->exit_status = 1;
					continue ;
				}
			}
			if (ft_strchr(cmd->argv[i], '='))
				help_function(cmd, table, i, check);
		}
	}
}

void	put_declare_x(t_table *table)
{
	int		i;
	char	**tmp;

	i = 0;
	while (table->declare_x[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 3));
	i = 0;
	while (table->declare_x[i])
	{
		if (ft_strchr(table->declare_x[i], '='))
		{
			tmp[i] = ft_strdup(table->declare_x[i]);
			tmp[i] = add_quotes_to_string(tmp[i]);
		}
		else
			tmp[i] = ft_strdup(table->declare_x[i]);
		i++;
	}
	tmp[i] = NULL;
	ft_putstr2d_fd(tmp, 1);
}

void	help_function(t_cmd *cmd, t_table *table, int i, int check)
{
	if (ft_strchr(cmd->argv[i], '+') && check_if_correct(cmd->argv[i]))
		the_plus(cmd, i, table);
	else
	{
		check = check_if_exist(cmd->argv[i], table->env, 1);
		if (check != -1)
		{
			table->env[check] = ft_strdup(cmd->argv[i]);
			check = 0;
		}
		else
			table->env = ft_add_env2(table->env, ft_strdup(cmd->argv[i]));
	}
}

void	ft_export(t_cmd *cmd, t_table *table)
{
	int		i;
	int		check;
	int		flag;

	flag = 0;
	check = 0;
	i = 1;
	sort_double_pointer_2(table->declare_x, ft_strlen_2d(table->declare_x));
	if (cmd->argv[1] == NULL)
	{
		put_declare_x(table);
		return ;
	}
	after_export(cmd, table, check);
	if (table->flag != 1)
		export_declare_x(table, cmd);
}
