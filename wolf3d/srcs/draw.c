/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 01:39:28 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 19:00:14 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w3d_pixel_to_img(int y, t_w3denv *e)
{
	int		i;

	i = e->r.cur_col * (e->bpp / 8) + y * e->sline;
	e->img_data[i] = e->m.color;
	e->img_data[++i] = e->m.color >> 8;
	e->img_data[++i] = e->m.color >> 16;
}

static void	w3d_get_frametime(t_w3denv *e)
{
	e->i.ti.oldtime = e->i.ti.time;
	gettimeofday(&e->i.ti.st, NULL);
	e->i.ti.time = (e->i.ti.st.tv_sec * 1000.0 + e->i.ti.st.tv_usec / 1000.0);
	e->i.ti.time /= 1000;
	e->i.ti.frametime = e->i.ti.time - e->i.ti.oldtime;
	e->p.move_speed = e->i.ti.frametime * (e->k.run == 1 ? 8 : 5);
	e->p.rot_speed = e->i.ti.frametime * 3;
}

static void	w3d_get_info(char *name, int i, int j, t_w3denv *e)
{
	char	*str;
	char	*str2;
	char	*tmp1;
	char	*tmp2;

	e->i.pos_y += 15;
	str = ft_itoa(i);
	str2 = ft_itoa(j);
	tmp1 = ft_strjoin(name, " X: ");
	tmp2 = ft_strjoin(tmp1, str);
	ft_strdel(&tmp1);
	tmp1 = ft_strjoin(tmp2, " | Y: ");
	ft_strdel(&tmp2);
	tmp2 = ft_strjoin(tmp1, str2);
	ft_strdel(&tmp1);
	mlx_string_put(e->mlx, e->win, 10, e->i.pos_y, 0xFFFFFF, tmp2);
	ft_strdel(&tmp2);
	ft_strdel(&str);
	ft_strdel(&str2);
}

static void	w3d_info(t_w3denv *e)
{
	char	*str;

	str = ft_itoa(1.0 / e->i.ti.frametime);
	e->i.pos_y = 10;
	mlx_string_put(e->mlx, e->win, 10, e->i.pos_y, 0xFFFFFF, str);
	ft_strdel(&str);
	e->i.pos_y += 20;
	mlx_string_put(e->mlx, e->win, 10, e->i.pos_y, 0xFFFFFF, e->m.cur_level);
	w3d_get_info("Position", e->i.pos[0], e->i.pos[1], e);
	w3d_get_info("Direction", e->p.dir[0] * 100, e->p.dir[1] * 100, e);
	w3d_get_info("Plane", e->r.plane[0] * 100, e->r.plane[1] * 100, e);
}

void		w3d_draw(t_w3denv *e)
{
	e->img = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->img_data = mlx_get_data_addr(e->img, &(e->bpp), &(e->sline), &(e->ed));
	w3d_raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
	w3d_get_frametime(e);
	if (e->i.enable == 1)
		w3d_info(e);
}
