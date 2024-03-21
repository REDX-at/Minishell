/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/03/18 22:22:58 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_env(char *str, char **env, pid_t pid, int last_exit)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!ft_strncmp(str, "$$", 3))
		return (ft_itoa((int)pid));
	if (!ft_strncmp(str, "$?", 3))
		return (ft_itoa(last_exit));
	while (env[i])
	{
		if (ft_strlen(env[i]) > ft_strlen(str))
			len = ft_strlen(env[i]);
		else
			len = ft_strlen(str);
		if (i % 2 == 0 && i != 1 && strncmp(str + 1, env[i], len) == 0)
		{
			i++;
			return (env[i]);
		}
		i++;
	}
	return (strdup(""));
}

void	ft_envr(t_elem *elem, char **env, int last_exit)
{
	int	i;

	i = 0;
	while (elem)
	{
		if (elem->type == ENV)
		{
			elem->type = WORD;
			elem->content = put_env(elem->content, env, elem->pid, last_exit);
		}
		if (elem->type == NEW_LINE)
		{
			elem->type = WORD;
			elem->content = strdup("\\n");
		}
		if (elem->content[0] == '\\' && elem->type == WORD
			&& elem->state == GENERAL)
			elem->content = ft_strdup(&elem->content[1]);
		else if (elem->type == ESCAPE)
		{
			elem->type = WORD;
			elem->content = ft_get_escape(elem->content[1], elem->state);
		}
		elem = elem->next;
	}
}

int	ft_count_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**env_copy(char **envp)
{
	char	**envs;
	int		size;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	size = 0;
	size = ft_count_env(envp);
	envs = (char **)malloc(sizeof(char *) * ((size * 2) + 1));
	if (envs == NULL)
		exit(1);
	while (envp[j])
	{
		l = env_len(envp[j]);
		envs[i] = ft_substr(envp[j], 0, env_len(envp[j]));
		i++;
		envs[i] = ft_substr(envp[j], l + 1, ft_strlen(envp[j] + l + 1));
		i++;
		j++;
	}
	envs[i] = NULL;
	return (envs);
}
