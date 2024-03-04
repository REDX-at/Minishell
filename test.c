/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:19:28 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/27 20:33:18 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}


int	ft_strlen_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i + 1] == '=')
			break;
		i++;
	}
	return (i);
}

void    function_to_dp(void)
{
    char str[] = "redxaaaa=alo";
    char str2[] = "redx";
    if (ft_strncmp(str, str2, ft_strlen_until_equal(str2)) == 0)
        printf("yes\n");
    else
        printf("no\n");
    
}
int main()
{
    function_to_dp();
}