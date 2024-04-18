/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/04/18 12:50:21 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int word_count(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	printf("str = %s\n", str);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			count++;
		}
		i+= len(str + i);
	}
	printf("count = %d\n", count);
	return (count);
}
void env(char **str, t_table *table, t_elem **elem, t_vars *vars)
{
	char *tmp;
	char *tmp2;
	char *env;
	char **envp;

	envp = env_copy(table->env);
	tmp = ft_substr(*str, 0, len(*str));
	env = put_env(tmp, envp, table);
	vars->env = word_count(env);
	printf("env = %d\n", vars->env);
	if(env[0] == '\0')
	{
		ft_lstadd_back(elem, ft_lstnew(ft_strdup("")));
		ft_lstlast(*elem)->state = GENERAL;
	}
	free(tmp);
	tmp2 = ft_substr(*str, len(*str), ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(env, tmp2);
	free(tmp2);
	free(env);
	ft_free(envp);
}
int	ft_listing(char **str, t_elem **elem, t_table *table, t_vars *vars)
{
	int		i;
	int		l;
	char	*content;
	char *tmp;
	char *tmp2;

	i = 0;
	l = 0;
	tmp = ft_substr(*str, 0, vars->i);
	tmp2 = ft_substr(*str, vars->i, ft_strlen(*str));
	free(*str);
	*str = ft_strdup(tmp2);
	free(tmp2);
	if ((*str)[i] == '$' && vars->Q == 0 && vars->redir == 0 && vars->env == 0)
		env(str, table, elem, vars);
	l = len(*str);
	content = (char *)malloc(l + 1);
	if (content == NULL)
		exit(1);
	if(ft_lstlast(*elem) && ((*str[i] == '"'
		&& ft_lstlast(*elem)->content[0] == '"')
		|| (*str[i] == '\'' && ft_lstlast(*elem)->content[0] == '\'')))
		ft_lstadd_back(elem, ft_lstnew(ft_strdup("")));
	while (i < l)
	{
		content[i] = (*str)[i];
		i++;
	}
	content[i] = '\0';
	ft_lstadd_back(elem, ft_lstnew(content));
	tmp2 = ft_strjoin(tmp, *str);
	free(*str);
	*str = ft_strdup(tmp2);
	free(tmp2);
	free(tmp);
	return (l);
}

int	ft_chek_if_escape(char c)
{
	if (c == 't' || c == 'b' || c == 'r' || c == '\\' || c == '\"' || c == '\''
		|| c == '$')
		return (1);
	return (0);
}

int	ft_else_token(t_elem *elem)
{
	if ((elem->content[0] == ' ' || elem->content[0] == '\t')
		&& elem->state == GENERAL)
		return (elem->type = WHITE_SPACE, 1);
	else if (elem->state != GENERAL && elem->content[0] == '\\'
		&& elem->content[1] == 'n')
		return (elem->type = NEW_LINE, 1);
	else if (elem->content[0] == '\'' && elem->state == GENERAL
		&& (!elem->prev || (elem->prev
				&& ft_strncmp(elem->prev->content, "\\", 2) != 0)
			|| (elem->prev && elem->prev->state != GENERAL
				&& ft_strncmp(elem->prev->content, "\\", 2) == 0)))
		return (elem->type = QOUTE, 1);
	else if (elem->content[0] == '"' && elem->state == GENERAL)
		return (elem->type = DOUBLE_QUOTE, 1);
	else if (elem->state == IN_DQUOTE && elem->content[0] == '\\'
		&& ft_chek_if_escape(elem->content[1]))
		return (elem->type = ESCAPE, 1);
	return (0);
}

void	ft_token(t_elem *elem)
{
		if (ft_else_token(elem))
			;
		else if (elem->content[0] == '|' && elem->state == GENERAL)
			elem->type = PIPE_LINE;
		else if (elem->content[0] == '>' && elem->content[1] != '>'
			&& elem->state == GENERAL)
			elem->type = REDIR_OUT;
		else if (elem->content[0] == '<' && elem->content[1] != '<'
			&& elem->state == GENERAL)
			elem->type = REDIR_IN;
		else if (elem->content[0] == '>' && elem->content[1] == '>'
			&& elem->state == GENERAL)
			elem->type = DREDIR_OUT;
		else if (elem->content[0] == '<' && elem->content[1] == '<'
			&& elem->state == GENERAL)
			elem->type = HERE_DOC;
		else
			elem->type = WORD;
}

void	ft_state(char **line, t_vars *vars, t_elem **elem, t_table *table)
{
	if (*line && (*line)[vars->i] == '"' && (vars->i == 0 || (*line)[vars->i - 1] != '\\')
		&& vars->DQ == 0 && vars->Q == 0 && vars->env == 0)
		(1) && (vars->DQ = 1, vars->closedQ = 1);
	else if (*line && (*line)[vars->i] == '\"' && vars->DQ == 1)
		(1) && (vars->DQ = 0, vars->closedQ = 0);
	else if (*line && (*line)[vars->i] == '\'' && (vars->i == 0
			|| (*line)[vars->i - 1] != '\\') && vars->Q == 0 && vars->DQ == 0
			&& vars->env == 0)
		(1) && (vars->Q = 1, vars->closedQ = 2);
	else if (*line && (*line)[vars->i] == '\'' && vars->Q == 1)
		(1) && (vars->Q = 0, vars->closedQ = 0);
	if (vars->i == vars->l)
	{
		vars->l += ft_listing(line, elem, table, vars);
		vars->last = ft_lstlast(*elem);
		if (vars->last)
		{
			vars->last->pid = table->pid;
			if ((vars->closedQ == 1 && vars->last->content[0] != '"'))
				vars->last->state = 0;
			else if (vars->closedQ == 2 && vars->last->content[0] != '\'')
				vars->last->state = 1;
			else
				vars->last->state = 2;
		}
		ft_token(vars->last);
		if(vars->last->type == HERE_DOC)
			vars->redir = 1;
		else if (vars->redir == 1 && vars->last->type == WORD)
			vars->redir = 0;
		if (vars->env != 0 && vars->last->type != WHITE_SPACE)
			(1) && (vars->last->state = IN_DQUOTE, vars->env--, vars->last->type = WORD);
	}
}
