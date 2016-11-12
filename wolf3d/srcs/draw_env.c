/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 10:16:49 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 18:57:17 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w3d_draw_floor_ceiling(t_w3denv *e)
{
	int	i;
	int	j;

	e->m.color = 0x707070;
	i = e->r.drawend - 1;
	if (e->r.drawend < 0)
		i = WIN_H - 1;
	while (++i < WIN_H)
		w3d_pixel_to_img(i, e);
	i = -1;
	e->m.color = 0x424242;
	j = e->r.drawstart;
	if (e->r.drawstart > WIN_H)
		j = WIN_H;
	while (++i < j)
		w3d_pixel_to_img(i, e);
}

static void	w3d_get_texid(t_w3denv *e)
{
	int	i;

	if (e->k.nsfw == 0)
	{
		e->m.texid = e->m.map[e->m.map_coord[0]][e->m.map_coord[1]] - 1;
		i = -1;
		while (++i < e->m.nb_doors)
		{
			if ((int)e->m.map_coord[0] == e->m.d[i].pos[0] &&
					(int)e->m.map_coord[1] == e->m.d[i].pos[1] &&
						e->p.side == e->m.d[i].side)
			{
				e->m.texid = 15;
				break ;
			}
		}
	}
	else
		e->m.texid = 23;
}

static void	w3d_draw_tex_walls_calc(t_w3denv *e)
{
	if (e->p.side == 0)
		e->r.wallx = e->r.raypos[1] + e->r.perpwalldist * e->r.raydir[1];
	else
		e->r.wallx = e->r.raypos[0] + e->r.perpwalldist * e->r.raydir[0];
	e->r.wallx -= floor(e->r.wallx);
	e->r.tex_x = e->r.wallx * TEX_W;
	if (e->p.side == 0 && e->r.raydir[0] > 0)
		e->r.tex_x = TEX_W - e->r.tex_x - 1;
	if (e->p.side == 1 && e->r.raydir[1] < 0)
		e->r.tex_x = TEX_W - e->r.tex_x - 1;
}

void		w3d_draw_tex_walls(t_w3denv *e)
{
	int	tmp;
	int y;

	w3d_get_texid(e);
	w3d_draw_tex_walls_calc(e);
	y = e->r.drawstart - 1;
	while (++y < e->r.drawend)
	{
		tmp = y * 256 - WIN_H * 128 + e->r.lineheight * 128;
		e->r.tex_y = ((tmp * TEX_H) / e->r.lineheight) / 256;
		tmp = e->r.tex_x * (e->t[e->m.texid]->bpp / 8) +
			e->r.tex_y * e->t[e->m.texid]->sline;
		e->m.color = (e->t[e->m.texid]->img_data[tmp] & 0xFF) +
			((e->t[e->m.texid]->img_data[tmp + 1] & 0xFF) << 8) +
				((e->t[e->m.texid]->img_data[tmp + 2] & 0xFF) << 16);
		w3d_pixel_to_img(y, e);
	}
}

void		w3d_draw_base_walls(t_w3denv *e)
{
	int	i;

	if (e->p.side == 0)
		e->m.color = (e->r.raydir[0] > 0 ? 0xAA0000 : 0x00AA00);
	else
		e->m.color = (e->r.raydir[1] > 0 ? 0x0000AA : 0xAAAA00);
	i = e->r.drawstart - 1;
	if (e->r.drawend < 0)
		e->r.drawend = WIN_H;
	while (++i < e->r.drawend)
		w3d_pixel_to_img(i, e);
}
