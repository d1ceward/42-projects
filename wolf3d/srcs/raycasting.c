/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 22:31:36 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/25 09:25:22 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	w3d_raycasting_calc(t_w3denv *e)
{
	if (e->p.side == 0)
		e->r.perpwalldist = fabs((e->m.map_coord[0] - e->r.raypos[0] +
			(1 - e->p.step[0]) / 2) / e->r.raydir[0]);
	else
		e->r.perpwalldist = fabs((e->m.map_coord[1] - e->r.raypos[1] +
			(1 - e->p.step[1]) / 2) / e->r.raydir[1]);
	e->r.lineheight = abs((int)(WIN_H / e->r.perpwalldist));
	e->r.drawstart = WIN_H / 2 - e->r.lineheight / 2;
	if (e->r.drawstart < 0)
		e->r.drawstart = 0;
	e->r.drawend = e->r.lineheight / 2 + WIN_H / 2;
	if (e->r.drawend >= WIN_H)
		e->r.drawend = WIN_H - 1;
}

static void	w3d_raycasting_dda(t_w3denv *e)
{
	while (e->p.hit == 0)
	{
		if (e->r.sidedist[0] < e->r.sidedist[1])
		{
			e->r.sidedist[0] += e->r.deltadist[0];
			e->m.map_coord[0] += e->p.step[0];
			e->p.side = 0;
		}
		else
		{
			e->r.sidedist[1] += e->r.deltadist[1];
			e->m.map_coord[1] += e->p.step[1];
			e->p.side = 1;
		}
		if (e->m.map[e->m.map_coord[0]][e->m.map_coord[1]] > 0)
			e->p.hit = 1;
	}
}

static void	w3d_raycasting_side(t_w3denv *e)
{
	if (e->r.raydir[0] < 0)
	{
		e->p.step[0] = -1;
		e->r.sidedist[0] = (e->r.raypos[0] - e->m.map_coord[0]) *
			e->r.deltadist[0];
	}
	else
	{
		e->p.step[0] = 1;
		e->r.sidedist[0] = (e->m.map_coord[0] + 1.0 - e->r.raypos[0]) *
			e->r.deltadist[0];
	}
	if (e->r.raydir[1] < 0)
	{
		e->p.step[1] = -1;
		e->r.sidedist[1] = (e->r.raypos[1] - e->m.map_coord[1]) *
			e->r.deltadist[1];
	}
	else
	{
		e->p.step[1] = 1;
		e->r.sidedist[1] = (e->m.map_coord[1] + 1.0 - e->r.raypos[1]) *
			e->r.deltadist[1];
	}
}

static void	w3d_raycasting_init(t_w3denv *e)
{
	e->p.camera_x = 2 * e->r.cur_col / (double)WIN_W - 1;
	e->r.raypos[0] = e->p.pos[0];
	e->r.raypos[1] = e->p.pos[1];
	e->i.pos[0] = e->p.pos[0];
	e->i.pos[1] = e->p.pos[1];
	e->r.raydir[0] = e->p.dir[0] + e->r.plane[0] * e->p.camera_x;
	e->r.raydir[1] = e->p.dir[1] + e->r.plane[1] * e->p.camera_x;
	e->m.map_coord[0] = e->r.raypos[0];
	e->m.map_coord[1] = e->r.raypos[1];
	e->r.deltadist[0] = sqrt(1 + (e->r.raydir[1] * e->r.raydir[1]) /
		(e->r.raydir[0] * e->r.raydir[0]));
	e->r.deltadist[1] = sqrt(1 + (e->r.raydir[0] * e->r.raydir[0]) /
		(e->r.raydir[1] * e->r.raydir[1]));
	e->p.hit = 0;
}

void		w3d_raycasting(t_w3denv *e)
{
	e->r.cur_col = -1;
	while (++e->r.cur_col < WIN_W)
	{
		w3d_raycasting_init(e);
		w3d_raycasting_side(e);
		w3d_raycasting_dda(e);
		w3d_raycasting_calc(e);
		w3d_draw_floor_ceiling(e);
		if (e->m.enable_tex == 1)
			w3d_draw_tex_walls(e);
		else
			w3d_draw_base_walls(e);
	}
}
