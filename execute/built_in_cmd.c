/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/31 08:03:02 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr2d_fd(char **str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1] != NULL)
			ft_putstr_fd("\n", fd);
		i++;
	}
	if (i != 0)
		ft_putstr_fd("\n", fd);
}

int	ft_strlen_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

int	ft_is_integer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	utils_for_exit(t_table *table, t_cmd *cmd, int flag)
{
	table->exit_status = ft_atoi(cmd->argv[1], &flag);
	if (flag)
	{
		table->exit_status = 255;
		ft_putstr_fd("exit\nmsh: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	ft_putstr_fd("exit\n", 2);
	exit(table->exit_status);
}

void	ft_exit(t_cmd *cmd, t_table *table)
{
	int	flag;

	flag = 0;
	if (cmd->argv[1] == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit(table->exit_status);
	}
	if (!ft_is_integer(cmd->argv[1]))
	{
		ft_putstr_fd("exit\nmsh: exit: ", 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		table->exit_status = 255;
		exit(255);
	}
	else if (ft_strlen_2d(cmd->argv) > 2)
	{
		ft_putstr_fd("exit\nmsh: exit: too many arguments\n", 2);
		table->exit_status = 1;
		if (cmd->pipe)
			exit(1);
	}
	else if (ft_is_integer(cmd->argv[1]))
		utils_for_exit(table, cmd, flag);
}
