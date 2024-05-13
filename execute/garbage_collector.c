/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:42:35 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/12 16:37:17 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_garbage	*ft_lstnews(void *content)
{
	t_garbage	*new_node;

	new_node = (t_garbage *)malloc(sizeof(t_garbage));
	if (!new_node)
		return (NULL);
    new_node->str = content;
	new_node->next = NULL;
	return (new_node);
}

t_garbage   *ft_lstnews_2d(void **content)
{
    t_garbage   *new_node;

    new_node = (t_garbage *)malloc(sizeof(t_garbage));
    if (!new_node)
        return (NULL);
    new_node->str = content;
    new_node->next = NULL;
    return (new_node);
}

void	ft_lstadds_back(t_garbage **lst, t_garbage *jdida)
{
	t_garbage	*tmp;

	if (!lst || !jdida)
		return ;
	if (!*lst)
	{
		*lst = jdida;
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->next = jdida;
			return ;
		}
		tmp = tmp->next;
	}
}

void	*garbage_collect(void *str, t_table *table, int size)
{
	str = (void *)malloc(size);
	if (!str)
	{
		perror("malloc");
        free_garbage(table);
		exit(EXIT_FAILURE);
	}
    ft_lstadds_back(&table->garbage, ft_lstnews(str));
    return (str);
}

void    **garbage_collect_2d(void **str, t_table *table, int size)
{
    str = (void **)malloc(size);
    if (!str)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_lstadds_back(&table->garbage, ft_lstnews_2d(str));
    return (str);
}

void    free_garbage(t_table *table)
{
    t_garbage   *tmp;

    tmp = table->garbage;
    while (tmp)
    {
        ft_putstr_fd(tmp->str, 1);
        ft_putstr_fd("\n", 1);
        tmp = tmp->next;
    }
    table->garbage = NULL;
}
