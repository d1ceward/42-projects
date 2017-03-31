/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 06:21:48 by flefebvr          #+#    #+#             */
/*   Updated: 2016/11/08 06:21:49 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>

typedef struct	s_msenv
{
	char	**cmd;
	char	**env;
}				t_msenv;

int				ms_builtin(t_msenv *e);
char			*ms_getenv(char **env, char *name);
int				ms_unsetenv(t_msenv *e, char *name);
int				ms_setenv(t_msenv *e, char *name, char *value);
void			ms_exec(char **env, char **cmd);
void			ms_error(char *msg, char *var);
void			ms_builtin_cd(t_msenv *e);

#endif
