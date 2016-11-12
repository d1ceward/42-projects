/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 13:34:21 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 18:38:22 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	w3d_get_door(int i, char *line, t_w3denv *e)
{
	int	j;

	e->pa.str = ft_strsplit(line, ' ');
	i -= 10 + e->pa.size_s;
	if ((e->m.d[i].pos[0] = ft_atoi(e->pa.str[1])) < 0 ||
			e->m.d[i].pos[0] > e->m.map_size[0])
		ft_exit("Wolf3d: Invalid door position", EXIT_FAILURE);
	if ((e->m.d[i].pos[1] = ft_atoi(e->pa.str[3])) < 0 ||
			e->m.d[i].pos[1] > e->m.map_size[1])
		ft_exit("Wolf3d: Invalid door position", EXIT_FAILURE);
	if ((e->m.d[i].side = ft_atoi(e->pa.str[5])) < 0 ||
			e->m.d[i].side > 1)
		ft_exit("Wolf3d: Invalid door side", EXIT_FAILURE);
	j = -1;
	while (++j < 7)
		ft_strdel(&e->pa.str[j]);
	free(e->pa.str);
}

void	w3d_get_exit(int i, char *line, t_w3denv *e)
{
	int	j;

	e->pa.str = ft_strsplit(line, ' ');
	i -= 11 + e->pa.size_sd;
	e->m.e[i].level_name = ft_strdup(e->pa.str[0]);
	if ((e->m.e[i].pos[0] = ft_atoi(e->pa.str[2])) < 0 ||
			e->m.e[i].pos[0] > e->m.map_size[0])
		ft_exit("Wolf3d: Invalid exit position", EXIT_FAILURE);
	if ((e->m.e[i].pos[1] = ft_atoi(e->pa.str[4])) < 0 ||
			e->m.e[i].pos[1] > e->m.map_size[1])
		ft_exit("Wolf3d: Invalid exit position", EXIT_FAILURE);
	j = -1;
	while (++j < 6)
		ft_strdel(&e->pa.str[j]);
	free(e->pa.str);
}
