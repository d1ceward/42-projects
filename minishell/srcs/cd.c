/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 09:59:08 by flefebvr          #+#    #+#             */
/*   Updated: 2017/03/29 09:59:11 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_cd_empty(t_msenv *e, char *cur_pwd)
{
	char	*new_pwd;

	if ((new_pwd = ms_getenv(e->env, "HOME")) != NULL)
	{
		ms_setenv(e, "OLDPWD", cur_pwd);
		chdir(new_pwd);
		ms_setenv(e, "PWD", new_pwd);
		free(new_pwd);
	}
	else
		ms_error("cd: home var not set", NULL);
}

static void	ms_cd_back(t_msenv *e, char *cur_pwd)
{
	char	*new_pwd;

	if ((new_pwd = ms_getenv(e->env, "OLDPWD")) != NULL)
	{
		ms_setenv(e, "OLDPWD", cur_pwd);
		chdir(new_pwd);
		ms_setenv(e, "PWD", new_pwd);
		free(new_pwd);
	}
	else
		ms_error("cd: oldpwd var not set", NULL);
}

static void	ms_cd_access(t_msenv *e, char *cur_pwd)
{
	char	*new_pwd;

	if (access(e->cmd[1], R_OK) == 0)
	{
		if (chdir(e->cmd[1]) == 0)
		{
			ms_setenv(e, "OLDPWD", cur_pwd);
			new_pwd = getcwd(NULL, 0);
			ms_setenv(e, "PWD", new_pwd);
			free(new_pwd);
		}
		else
			ms_error("cd: not a directory: ", e->cmd[1]);
	}
	else
		ms_error("cd: permission denied: ", e->cmd[1]);
}

void		ms_builtin_cd(t_msenv *e)
{
	char	*cur_pwd;
	int		i;

	i = 0;
	while (e->cmd[i])
		++i;
	cur_pwd = getcwd(NULL, 0);
	if (i > 2)
		ms_error("cd: too many arguments", NULL);
	else if (i == 1)
		ms_cd_empty(e, cur_pwd);
	else if (e->cmd[1][0] == '-' && e->cmd[1][1] == '\0')
		ms_cd_back(e, cur_pwd);
	else if (access(e->cmd[1], F_OK) == 0)
		ms_cd_access(e, cur_pwd);
	else
		ms_error("cd: no such file or directory: ", e->cmd[1]);
	free(cur_pwd);
}
