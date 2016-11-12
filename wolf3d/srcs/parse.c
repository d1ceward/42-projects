/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 13:30:21 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 18:39:34 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	w3d_get_dirplane(t_w3denv *e)
{
	if ((e->p.dir[0] = (double)ft_atoi(e->pa.str[9])) < -1 || e->p.dir[0] > 1)
		ft_exit("Wolf3d: Invalid dir x", EXIT_FAILURE);
	if ((e->p.dir[1] = (double)ft_atoi(e->pa.str[11])) < -1 || e->p.dir[1] > 1)
		ft_exit("Wolf3d: Invalid dir y", EXIT_FAILURE);
	if ((e->r.plane[0] = (double)ft_atoi(e->pa.str[13]) / 100) < -0.66 ||
			e->r.plane[0] > 0.66)
		ft_exit("Wolf3d: Invalid plane x", EXIT_FAILURE);
	if ((e->r.plane[1] = (double)ft_atoi(e->pa.str[15]) / 100) < -0.66 ||
			e->r.plane[1] > 0.66)
		ft_exit("Wolf3d: Invalid plane y", EXIT_FAILURE);
}

static void	w3d_get_size(char *line, t_w3denv *e)
{
	int i;

	e->pa.str = ft_strsplit(line, ' ');
	if ((e->m.map_size[0] = ft_atoi(e->pa.str[1])) < 0 ||
			e->m.map_size[0] > MAX_MAP_H)
		ft_exit("Wolf3d: Invalid map size", EXIT_FAILURE);
	if ((e->m.map_size[1] = ft_atoi(e->pa.str[3])) < 0 ||
			e->m.map_size[1] > MAX_MAP_W)
		ft_exit("Wolf3d: Invalid map size", EXIT_FAILURE);
	if ((e->m.nb_doors = ft_atoi(e->pa.str[5])) < 0)
		ft_exit("Wolf3d: Invalid doors numbers", EXIT_FAILURE);
	if ((e->m.nb_exits = ft_atoi(e->pa.str[7])) < 0)
		ft_exit("Wolf3d: Invalid exits numbers", EXIT_FAILURE);
	w3d_get_dirplane(e);
	w3d_get_mapformat_value(e);
	w3d_parse_malloc(e);
	i = -1;
	while (++i < 17)
		ft_strdel(&e->pa.str[i]);
	free(e->pa.str);
}

static void	w3d_get_start_pos(char *line, t_w3denv *e)
{
	int	i;

	e->pa.str = ft_strsplit(line, ' ');
	if ((e->p.pos[0] = ft_atoi(e->pa.str[1]) + 0.5) >= e->m.map_size[0] &&
			e->p.pos[0] > 0)
		ft_exit("Wolf3d: Invalid starting position X", EXIT_FAILURE);
	e->r.raypos[0] = e->p.pos[0];
	if ((e->p.pos[1] = ft_atoi(e->pa.str[3]) + 0.5) >= e->m.map_size[1] &&
			e->p.pos[1] > 0)
		ft_exit("Wolf3d: Invalid starting position Y", EXIT_FAILURE);
	e->r.raypos[1] = e->p.pos[1];
	i = -1;
	while (++i < 5)
		ft_strdel(&e->pa.str[i]);
	free(e->pa.str);
}

static void	w3d_get_map(int i, char *line, t_w3denv *e)
{
	int		j;
	int		k;

	e->pa.str = ft_strsplit(line, ' ');
	j = -1;
	while (++j < e->m.map_size[0])
	{
		if (!e->pa.str[j])
			ft_exit("Wolf3d: Invalid map", EXIT_FAILURE);
		e->m.map[i - 9][j] = ft_atoi(e->pa.str[j]);
	}
	k = -1;
	while (++k < j + 1)
		ft_strdel(&e->pa.str[k]);
	free(e->pa.str);
}

void		w3d_parse(t_w3denv *e)
{
	int		i;
	char	*line;

	i = 1;
	while ((e->pa.code_gnl = get_next_line(e->pa.fd, &line)) > 0)
	{
		if (i == 3)
			e->m.cur_level = ft_strndup(line, 8);
		else if (i == 5)
			w3d_get_size(line, e);
		else if (i == 7)
			w3d_get_start_pos(line, e);
		else if (i >= 9 && i < 9 + e->pa.size_s)
			w3d_get_map(i, line, e);
		else if (i >= 10 + e->pa.size_s && i < 10 + e->pa.size_sd)
			w3d_get_door(i, line, e);
		else if (i >= 11 + e->pa.size_sd && i < 11 + e->pa.size_sde)
			w3d_get_exit(i, line, e);
		ft_strdel(&line);
		i++;
	}
	if (e->pa.code_gnl == -1 || i != (11 + e->pa.size_sde))
		ft_exit("Wolf3d: File parse error", EXIT_FAILURE);
	ft_strdel(&line);
}
