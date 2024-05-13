/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:24:57 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/13 19:23:25 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
// table len
int g_status = 0;
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	for_init(t_table *table)
{
	table->gar = 0;
	table->garbage = malloc(sizeof(char *) * 255);
	table->alpha = getcwd(NULL, 0);
	table->declare_x = NULL;
	table->last_arg = ft_strdup("mini");
	table->pwd_env = NULL;
	table->exit_status = 0;
	table->tmp_in = 0;
	table->tmp_out = 0;
	table->flag = 0;
	table->flag_old = 0;
	table->i = 0;
	table->check = 0;
	table->j = 0;
	table->s = 0;
	table->l = 0;
}

void	loop_inside_init(t_table *table, char **envp, int i, int shlvl)
{
	char	*tmp;

	while (envp[i])
	{
		if(ft_strncmp(envp[i], "_=", 2) == 0)
			table->env[i] = ft_strdup("_=/usr/bin/env");
		else
		{
			if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			{
				shlvl = ft_atoi(envp[i] + 6, 0);
				shlvl++;
				free(envp[i]);
				tmp = ft_itoa(shlvl);
				envp[i] = ft_strjoin("SHLVL=", tmp);
				free(tmp);
			}
			table->env[i] = ft_strdup(envp[i]);
		// free(envp[i]);
		}
		i++;
	}
	table->env[i] = NULL;	
}

void	if_null(t_table *table)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	table->env[0] = ft_strjoin("PWD=", tmp);
	free(tmp);
	table->env[1] = ft_strdup("SHLVL=1");
	table->env[2] = ft_strdup("_=/usr/bin/env");
	table->env[3] = ft_strdup("PATH=/Users/aitaouss/.brew/bin:/usr/local/bin:/usr/bin:/bin"
		":/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin");
	table->env[4] = ft_strdup("SHELL=/bin/msh");
	table->env[5] = NULL;
	table->red = 1;
}

// init table
t_table	*ft_init_table(char **envp)
{
	t_table		*table;
	int			i;
	int			shlvl;
	char		*tmp;

	tmp = NULL;
	shlvl = 0;
	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->env = (char **)malloc(sizeof(char *) * (255));
	if (!table->env)
		return (NULL);
	table->red = 0;
	if (envp[0] == NULL)
		if_null(table);
	else
		loop_inside_init(table, envp, i, shlvl);
	for_init(table);
	return (table);
}

void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_status == 2)
		{
			g_status = 1;
			printf("\n");
			return;
		}
		g_status = 1;
		printf("\n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
	}
}

void ft_free_elem(t_elem **elem)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = *elem;
	while (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*elem = NULL;
}

void ft_cmd_free(t_cmd **cmd)
{
	t_elem	*tmp;
	t_cmd	*tmp_cmd;

	tmp = NULL;
	if((*cmd))
		ft_free_elem(&(*cmd)->elem);
	while ((*cmd))
	{
		if((*cmd)->cmd)
			free((*cmd)->cmd);
		if ((*cmd)->argv)
			ft_free((*cmd)->argv);
		if((*cmd)->file)
			ft_free((*cmd)->file);
		if((*cmd)->redir)
			ft_free((*cmd)->redir);
		tmp_cmd = (*cmd)->next;
		free(*cmd);
		(*cmd) = tmp_cmd;
	}
	(*cmd) = NULL;
}

void	ft_built_in(t_cmd **cmd, t_table *table)
{
	t_cmd	*tmp;
	
	tmp = *cmd;
	table->count_cmd = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "cd") || ft_strcmp(tmp->cmd, "pwd") ||
			ft_strcmp(tmp->cmd, "echo") || ft_strcmp(tmp->cmd, "env") ||
			ft_strcmp(tmp->cmd, "export") || ft_strcmp(tmp->cmd, "unset") || ft_strcmp(tmp->cmd, "exit"))
			tmp->is_builtin = 1;
		table->count_cmd++;
		tmp = tmp->next;
	} 
}

char	**the_twode(char **twode)
{
	int		index;
	char	**new_twode;

	index = 0;
	while (twode[index])
		index++;
	new_twode = (char **)malloc(sizeof(char *) * (index + 1));
	if (!new_twode)
		return (NULL);
	index = 0;
	while (twode[index])
	{
		new_twode[index] = ft_strdup(twode[index]);
		index++;
	}
	new_twode[index] = NULL;
	return (new_twode);
}

pid_t ft_get_pid()
{
	pid_t pid;

	pid = 0;
	pid = fork();
	if (pid < 1)
		exit(0);
	pid--;
	return(pid); 
}

void sort_double_pointer_2(char **array, int size)
{
    int i = 0;
    char *temp;
    int sorted = 0;

    while (!sorted)
	{
        sorted = 1;
        i = 0;
        while (i < size - 1)
		{
			if (array[i] && array[i + 1])
			{
				if (array[i][11] > array[i + 1][11])
				{
					temp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = temp;
					sorted = 0;
				}
			}
            i++;
        }
        size--;
    }
}

char	**remove_old_pwd(char **env)
{
	int	i;
	int	j;
	int	len;
	char	**new_env;

	i = 0;
	j = 0;
	len = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			len++;
		i++;
	}
	new_env = (char **)malloc(sizeof(char *) * (i - len + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}
char	**ft_strdup_2d(char **str)
{
	int		i;
	char	**new_str;

	i = 0;
	while (str[i])
		i++;
	new_str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	new_str[i] = NULL;
	return (new_str);

}

char	**alloc_env(char **env)
{
    int		i;
    char	**new_env;
    char    *tmp;
    char    *tmp2;
	int		j;

	j = 0;
    i = 0;
    while (env[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * 255);
    if (!new_env)
        return (NULL);
    i = 0;
    while (env[i])
    {
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
        	tmp2 = ft_strdup(env[i]);
        	tmp = ft_strjoin("declare -x ", tmp2);
        	if (!tmp)
        	    return (free(tmp2), NULL);
        	free(tmp2);
        	new_env[j] = ft_strdup(tmp);
        	free(tmp);
			j++;
		}
		i++;
    }
	new_env[j] = ft_strdup("declare -x OLDPWD");
    new_env[j + 1] = NULL;
    return (new_env);
}

void	f()
{
	system("leaks minishell");
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_table	*table;
	pid_t pid;

	if(isatty(0) == 0)
		return (0);
	(void)argc;
	(void)argv;
	cmd = NULL;
	g_status = 0;
	// atexit(f);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	envp = remove_old_pwd(envp);
	table = ft_init_table(envp);
	table->var = "➜  minishell ";
	table->declare_x = alloc_env(table->env);
	table->pwd_env = getcwd(NULL, 0);
	table->pid =  ft_get_pid();
	pid = table->pid;
	while (1)
	{
		line = readline(RED"➜  "RED""BOLD"minishell "RESET);
		if(g_status == 1)
			table->exit_status = 1;
		g_status = 0;
		if(line)
		{
			add_history(line);
			if (line[0] != '\0')
				ft_parsing(line, &cmd, table);
			ft_built_in(&cmd, table);
			if (cmd)
				execute_for_cmd(cmd, table);
			ft_cmd_free(&cmd);
		}
		if (!line)
		{
			ft_putstr_fd("exit", 1);
			ft_putstr_fd("\n", 1);
			exit(0);
		}
		// printf("%p\n", line);
	}
}
