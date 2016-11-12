/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 15:18:43 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 18:47:44 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	w3d_parse_malloc(t_w3denv *e)
{
	int	i;

	if (e->m.nb_doors > 0)
		if ((e->m.d = (t_w3ddoor*)malloc(sizeof(t_w3ddoor) *
				e->m.nb_doors)) == NULL)
			ft_exit("Wolf3d: Malloc failed", EXIT_FAILURE);
	if (e->m.nb_exits > 0)
		if ((e->m.e = (t_w3dexit*)malloc(sizeof(t_w3dexit) *
				e->m.nb_exits)) == NULL)
			ft_exit("Wolf3d: Malloc failed", EXIT_FAILURE);
	if ((e->m.map = (int**)ft_memalloc(sizeof(int*) *
			e->m.map_size[1])) == NULL)
		ft_exit("Wolf3d: Malloc failed", EXIT_FAILURE);
	i = -1;
	while (++i < e->m.map_size[1])
		if ((e->m.map[i] = (int*)ft_memalloc(sizeof(int) *
				e->m.map_size[0])) == NULL)
			ft_exit("Wolf3d: Malloc failed", EXIT_FAILURE);
}

void	w3d_parse_free(t_w3denv *e)
{
	int	i;

	ft_strdel(&e->m.cur_level);
	if (e->m.nb_doors > 0)
		free(e->m.d);
	if (e->m.nb_exits > 0)
	{
		i = -1;
		while (++i < e->m.nb_exits)
			ft_strdel(&e->m.e[i].level_name);
		free(e->m.e);
	}
	i = -1;
	while (++i < e->m.map_size[1])
		free((void*)e->m.map[i]);
	free(e->m.map);
}

void	w3d_get_mapformat_value(t_w3denv *e)
{
	e->pa.size_s = e->m.map_size[1];
	e->pa.size_sd = e->m.map_size[1] + e->m.nb_doors;
	e->pa.size_sde = e->m.map_size[1] + e->m.nb_doors + e->m.nb_exits;
}

void	w3d_level_swithcer(int i, t_w3denv *e)
{
	char *tmp;
	char *tmp2;

	if (i < 0)
		tmp = ft_strjoin("./map/", e->m.cur_level);
	else
		tmp = ft_strjoin("./map/", e->m.e[i].level_name);
	tmp2 = ft_strjoin(tmp, ".w3dmf");
	ft_strdel(&tmp);
	if ((e->pa.fd = open(tmp2, O_RDONLY)) < 0)
		ft_exit("Wolf3d: Failed to open map file", EXIT_FAILURE);
	ft_strdel(&tmp2);
	w3d_parse_free(e);
	w3d_parse(e);
	close(e->pa.fd);
}
