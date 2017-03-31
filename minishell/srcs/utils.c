/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 22:54:15 by flefebvr          #+#    #+#             */
/*   Updated: 2016/11/14 22:54:16 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_error(char *msg, char *var)
{
	ft_putstr_fd(msg, 2);
	if (var != NULL)
		ft_putendl_fd(var, 2);
	else
		ft_putchar_fd('\n', 2);
}

char	*ms_getenv(char **env, char *name)
{
	size_t	len;
	char	**tmp1;
	char	*tmp2;

	len = ft_strlen(name);
	tmp1 = env;
	while ((tmp2 = *tmp1) != NULL)
	{
		if (ft_strncmp(*tmp1, name, len) == 0 && tmp2[len] == '=')
			return (ft_strdup(tmp2 + len + 1));
		++tmp1;
	}
	return (NULL);
}

int		ms_unsetenv(t_msenv *e, char *name)
{
	size_t	len;
	char	**tmp1;
	char	**tmp2;

	len = ft_strlen(name);
	tmp1 = e->env;
	while (*tmp1 != NULL)
		if (ft_strncmp(*tmp1, name, len) == 0 && (*tmp1)[len] == '=')
		{
			tmp2 = tmp1;
			free(*tmp2);
			while (*tmp2 != NULL)
			{
				*tmp2 = *(tmp2 + 1);
				++tmp2;
			}
			return (1);
		}
		else
			++tmp1;
	return (0);
}

int		ms_setenv(t_msenv *e, char *name, char *value)
{
	char			**new_env;
	char			*tmp;
	unsigned long	env_len;

	ms_unsetenv(e, name);
	if (!(tmp = (char *)malloc(ft_strlen(name) + ft_strlen(value) + 2)))
		return (-1);
	ft_strcpy(tmp, name);
	ft_strcat(tmp, "=");
	ft_strcat(tmp, value);
	env_len = 0;
	while (e->env[env_len] != NULL)
		++env_len;
	if (!(new_env = (char **)malloc(sizeof(char *) * (env_len + 2))))
		return (-1);
	ft_memcpy(new_env, e->env, sizeof(char *) * env_len);
	free(e->env);
	e->env = new_env;
	e->env[env_len] = tmp;
	e->env[env_len + 1] = NULL;
	return (0);
}

void	ms_exec(char **env, char **cmd)
{
	char	**paths;
	char	*tmp;
	int		code;
	pid_t	pid;

	if ((pid = fork()) != 0)
		waitpid(pid, NULL, 0);
	else
	{
		tmp = ms_getenv(env, "PATH");
		paths = (tmp != NULL ? ft_strsplit(tmp, ':') : NULL);
		code = -1;
		while (paths != NULL && *paths != NULL)
		{
			code = execve(ft_stradd(ft_strjoin(*paths, "/"), *cmd), cmd, env);
			paths++;
		}
		if (code == -1 && execve(*cmd, cmd, env) == -1)
			ms_error("minishell: command not found: ", *cmd);
		exit(code);
	}
}
