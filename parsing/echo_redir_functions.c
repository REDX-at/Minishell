/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_redir_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/04/16 23:12:17 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_comp_n(char *str, t_elem *elem)
{
	int	i;

	i = 0;
	if ((elem->state == IN_DQUOTE && (elem->prev->type != DOUBLE_QUOTE
				|| elem->next->type != DOUBLE_QUOTE))
		|| (elem->state == IN_QUOTE
			&& (elem->prev->type != QOUTE || elem->next->type != QOUTE)))
		return (1);
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if (str[i] == '\0' && i > 1)
		return (0);
	return (1);
}

void	ft_count_echo_spaces(t_vars *vars, t_elem *elem)
{
	if (vars->spaces == 0 && vars->redir == 0 && vars->echo == 1 && elem->prev
		&& elem->type != WHITE_SPACE && elem->prev->type == WHITE_SPACE)
	{
		vars->size++;
		if (elem->type == WORD)
			(1) && (vars->size++);
		vars->spaces = 0;
	}
	else if (elem->type != DOUBLE_QUOTE && elem->type != QOUTE
		&& elem->type != WHITE_SPACE)
	{
		if (vars->redir == 1)
			vars->redir = 0;
		else
			vars->size++;
		(1) && (vars->spaces = 0);
	}
}

void	echo_spaces(t_vars *vars, t_elem *elem)
{
	if (vars->spaces == 0 && vars->redir == 0 && vars->echo == 1
		&& elem->type == WORD)
	{
		vars->l_cmd->argv[vars->j] = strdup(" ");
		(1) && (vars->j++, vars->spaces = 0);
		
		vars->l_cmd->argv[vars->j] = NULL;
	}
}

void	fill_redir_file(t_elem *elem, t_vars *vars, t_cmd **cmd)
{
	if (elem->type >= REDIR_IN && elem->type <= DREDIR_OUT)
	{
		ft_allocate_redir(elem, vars, cmd);
		vars->l_cmd->redir[vars->i] = ft_strdup(elem->content);
		vars->redir = 1;
	}
	else if (vars->redir == 1 && elem->type == WORD)
	{
		vars->l_cmd->file[vars->i] = ft_strdup(elem->content);
		(1) && (vars->l_cmd->state = elem->state, vars->redir = 0);
		(1) && (vars->prev_is_redir = 1, vars->i++);
		if (vars->rdrs == 1)
		{
			vars->l_cmd->file[vars->i] = NULL;
			vars->l_cmd->redir[vars->i] = NULL;
		}
		vars->rdrs--;
	}
	else if (vars->boolien == 1 && elem->type == WORD)
	{
		vars->l_cmd->argv[vars->j] =  ft_strdup(elem->content);
		(1) && (vars->j++, vars->l_cmd->argv[vars->j] = NULL);
		if ((vars->j != 1))
			vars->spaces = 0;
	}
}

void	ft_allocate_redir(t_elem *elem, t_vars *vars, t_cmd **cmd)
{
	if (vars->boolien == 0 && vars->redir == 0 && vars->rdrs == 0)
	{
		ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(NULL));
		vars->l_cmd = ft_lstlast_cmd(*cmd);
	}
	if (vars->rdrs == 0)
	if (vars->rdrs == 0)
	{
		vars->size = ft_count_argv(elem, &vars->rdrs, 1);
		vars->l_cmd->redir = (char **)malloc(sizeof(char *) * (vars->rdrs + 1));
		if (vars->l_cmd->redir == NULL)
			exit(1);
		vars->l_cmd->file = (char **)malloc(sizeof(char *) * (vars->rdrs + 1));
		if (vars->l_cmd->file == NULL)
			exit(1);
		vars->l_cmd->redir[vars->rdrs] = NULL;
		vars->l_cmd->file[vars->rdrs] = NULL;
	}
}
