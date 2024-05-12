/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:57:59 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/11 18:58:08 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_argv(t_elem *elem, int *redirs, int rdr)
{
	t_vars	vars;

	ft_memset(&vars, 0, sizeof(vars));
	while (elem && elem->type != PIPE_LINE)
	{
		if (vars.n == 0 && vars.echo == 1 && !ft_comp_n(elem->content))
			(1) && (vars.spaces = 1, vars.n = 1);
		else if (vars.echo == 0 && ft_strncmp(elem->content, "echo", 5) == 0)
			(1) && (vars.spaces = 1, vars.size++, vars.echo = 1);
		else if (rdr == 1 && (elem->type == REDIR_IN || elem->type == REDIR_OUT
				|| elem->type == HERE_DOC || elem->type == DREDIR_OUT))
			(1) && ((*redirs)++, vars.redir = 1, vars.n = 1);
		else
			ft_count_echo_spaces(&vars, elem);
		if (elem->type == DOUBLE_QUOTE || elem->type == QOUTE)
			vars.spaces = 0;
		elem = elem->next;
	}
	return (vars.size);
}
