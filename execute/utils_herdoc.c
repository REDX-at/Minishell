/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:41 by aitaouss          #+#    #+#             */
/*   Updated: 2024/04/12 17:06:46 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_env(char **line, t_cmd *cmd)
{
	int		i;
	char	**env;

	i = 0;
	cmd->table->l = 0;
	if (cmd->state == IN_QUOTE || ft_strchr(*line, '$') == NULL)
		return ;
	env = env_copy(cmd->table->env);
	for_put_env(line, cmd, env, i);
}
