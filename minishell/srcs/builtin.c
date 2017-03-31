/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 06:21:32 by flefebvr          #+#    #+#             */
/*   Updated: 2016/11/30 10:08:09 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_builtin_echo(t_msenv *e)
{
	int	i;
	int	test;

	if (e->cmd[1] != NULL)
	{
		i = (ft_strcmp(e->cmd[1], "-n") == 0 ? 1 : 0);
		test = (i == 1 ? 2 : 1);
		while (e->cmd[++i] != NULL)
		{
			if (i != test)
				ft_putchar(' ');
			ft_putstr(e->cmd[i]);
		}
		if (test != 2)
			ft_putchar('\n');
	}
	else
		ft_putchar('\n');
}

static void	ms_builtin_env(t_msenv *e)
{
	int	i;

	if (e->cmd[1] == NULL)
	{
		i = -1;
		while (e->env[++i] != NULL)
			ft_putendl(e->env[i]);
	}
	else
		ms_error("env: too many arguments: ", e->cmd[1]);
}

static void	ms_builtin_setenv(t_msenv *e)
{
	int	i;

	i = 0;
	while (e->cmd[i] != NULL)
		++i;
	if (i == 1)
		ms_error("setenv: empty arguments", NULL);
	else if (i > 3)
		ms_error("setenv: too many arguments", NULL);
	else if (ft_strchr(e->cmd[1], '=') != NULL)
		ms_error("setenv: invalid var path name", NULL);
	else if (i == 2)
		ms_setenv(e, e->cmd[1], "");
	else if (i == 3)
		ms_setenv(e, e->cmd[1], e->cmd[2]);
}

static void	ms_builtin_unsetenv(t_msenv *e)
{
	if (e->cmd[1] == NULL)
		ms_error("unsetenv: empty arguments", NULL);
	else if (e->cmd[2] != NULL)
		ms_error("unsetenv: too many arguments", NULL);
	else if (!ms_unsetenv(e, e->cmd[1]))
		ms_error("unsetenv: no env variable called: ", e->cmd[1]);
}

int			ms_builtin(t_msenv *e)
{
	char *tmp;

	if (ft_strcmp(e->cmd[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (ft_strcmp(e->cmd[0], "cd") == 0)
		ms_builtin_cd(e);
	else if (ft_strcmp(e->cmd[0], "echo") == 0)
		ms_builtin_echo(e);
	else if (ft_strcmp(e->cmd[0], "env") == 0)
		ms_builtin_env(e);
	else if (ft_strcmp(e->cmd[0], "setenv") == 0)
		ms_builtin_setenv(e);
	else if (ft_strcmp(e->cmd[0], "unsetenv") == 0)
		ms_builtin_unsetenv(e);
	else if (ft_strcmp(e->cmd[0], "pwd") == 0)
	{
		tmp = getcwd(NULL, 0);
		ft_putendl(tmp);
		free(tmp);
	}
	else
		return (0);
	return (1);
}
