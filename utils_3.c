/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:21:29 by aitaouss          #+#    #+#             */
/*   Updated: 2024/04/01 00:08:00 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// copy env function
char	**copy_the_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*copy_the_str(char *str, int *s, int flag)
{
	int		k;
	char	*tmp_2;

	tmp_2 = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	*s = 0;
	k = 0;
	while (str[*s] != '=')
		(*s)++;
	if (flag)
		(*s)++;
	while (str[*s])
	{
		tmp_2[k] = str[*s];
		k++;
		(*s)++;
	}
	tmp_2[k] = '\0';
	*s = 0;
	while (str[*s] != '=')
		(*s)++;
	return (tmp_2);
}

void	malloc_pro(char **str, char **str2, char **str3, char *argv)
{
	int	i;
	int	s;

	s = 0;
	i = -1;
	*str = malloc(sizeof(char) * 255);
	*str2 = malloc(sizeof(char) * 255);
	*str3 = malloc(sizeof(char) * 255);
	while (argv[++i])
	{
		if (argv[i] == '=')
		{
			i++;
			break ;
		}
	}
	while (argv[i])
	{
		(*str3)[s] = argv[i];
		s++;
		i++;
	}
	(*str3)[i] = '\0';
}
