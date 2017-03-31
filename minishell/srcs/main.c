/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 06:21:39 by flefebvr          #+#    #+#             */
/*   Updated: 2016/11/08 06:21:42 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_signals(int i)
{
	(void)i;
	signal(SIGQUIT, SIG_DFL);
}

static int	ms_prompt(t_msenv *e)
{
	char		*line;
	int			i;

	ft_putstr("$> ");
	while (get_next_line(0, &line))
	{
		i = -1;
		while (line[++i])
			if (line[i] == '\t')
				line[i] = ' ';
		e->cmd = ft_strsplit(line, ' ');
		free(line);
		if (*e->cmd != NULL)
			if (ms_builtin(e) == 0)
				ms_exec(e->env, e->cmd);
		ft_putstr("$> ");
		i = -1;
		while (e->cmd[++i] != NULL)
			free(e->cmd[i]);
		free(e->cmd);
	}
	return (EXIT_FAILURE);
}

static void	env_clone(t_msenv *e, char **env)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	while (env[i] != NULL)
		++i;
	if (!(e->env = (char**)ft_memalloc(sizeof(char *) * (i + 1))))
		ft_exit("minishell: memory error", EXIT_FAILURE);
	i = 0;
	while (env[i] != NULL)
	{
		j = ft_strlen(env[i]) + 1;
		if (!(e->env[i] = (char*)ft_memalloc(sizeof(char) * j)))
			ft_exit("minishell: memory error", EXIT_FAILURE);
		ft_strcpy(e->env[i], env[i]);
		++i;
	}
}

int			main(void)
{
	t_msenv		*e;
	extern char	**environ;
	char		*shlvl;
	char		*tmp;

	if ((e = (t_msenv*)ft_memalloc(sizeof(t_msenv))) == NULL)
		ft_exit("minishell: memory error", EXIT_FAILURE);
	env_clone(e, environ);
	if ((tmp = ms_getenv(e->env, "SHLVL")) != NULL)
	{
		shlvl = ft_itoa(ft_atoi(tmp) + 1);
		free(tmp);
	}
	else
		shlvl = ft_strdup("1");
	ms_setenv(e, "SHLVL", shlvl);
	free(shlvl);
	signal(SIGINT, ms_signals);
	return (ms_prompt(e));
}
