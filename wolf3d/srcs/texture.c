/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 05:51:48 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/22 05:51:50 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	w3d_fill_texture(int x, char *str, t_w3denv *e)
{
	e->t[x]->xpm = mlx_xpm_file_to_image(e->mlx, str,
		&(e->t[x]->size[0]), &(e->t[x]->size[1]));
	e->t[x]->img_data = mlx_get_data_addr(e->t[x]->xpm,
		&(e->t[x]->bpp), &(e->t[x]->sline), &(e->t[x]->ed));
}

static void	w3d_load_walls(t_w3denv *e)
{
	w3d_fill_texture(0, "./assets/textures/blue_brick1.xpm", e);
	w3d_fill_texture(1, "./assets/textures/blue_brick2.xpm", e);
	w3d_fill_texture(2, "./assets/textures/cell.xpm", e);
	w3d_fill_texture(3, "./assets/textures/cell_skeleton.xpm", e);
	w3d_fill_texture(4, "./assets/textures/grey_brick1.xpm", e);
	w3d_fill_texture(5, "./assets/textures/grey_brick2.xpm", e);
	w3d_fill_texture(6, "./assets/textures/grey_brick_hitler.xpm", e);
	w3d_fill_texture(7, "./assets/textures/grey_brick_eagle.xpm", e);
	w3d_fill_texture(8, "./assets/textures/grey_brick_flag.xpm", e);
	w3d_fill_texture(9, "./assets/textures/wood.xpm", e);
	w3d_fill_texture(10, "./assets/textures/wood_eagle.xpm", e);
	w3d_fill_texture(11, "./assets/textures/wood_hitler.xpm", e);
	w3d_fill_texture(12, "./assets/textures/elevator.xpm", e);
	w3d_fill_texture(13, "./assets/textures/elevator_up.xpm", e);
	w3d_fill_texture(14, "./assets/textures/elevator_down.xpm", e);
	w3d_fill_texture(15, "./assets/textures/door_wall.xpm", e);
	w3d_fill_texture(16, "./assets/textures/entrance_door.xpm", e);
	w3d_fill_texture(17, "./assets/textures/purple.xpm", e);
	w3d_fill_texture(18, "./assets/textures/purple_blood.xpm", e);
	w3d_fill_texture(19, "./assets/textures/steel.xpm", e);
	w3d_fill_texture(20, "./assets/textures/red_brick.xpm", e);
	w3d_fill_texture(21, "./assets/textures/red_brick_flag.xpm", e);
	w3d_fill_texture(22, "./assets/textures/red_brick_swastika.xpm", e);
}

void		w3d_load_tex(t_w3denv *e)
{
	int	i;

	if ((e->t = (t_w3dtex**)malloc(sizeof(t_w3dtex*) * TEX_NB)) == NULL)
		ft_exit("Wolf3d: Malloc failed", EXIT_FAILURE);
	i = -1;
	while (++i < TEX_NB)
		if ((e->t[i] = (t_w3dtex*)malloc(sizeof(t_w3dtex))) == NULL)
			ft_exit("Wolf3d: Malloc failed", EXIT_FAILURE);
	w3d_load_walls(e);
	w3d_fill_texture(23, "./assets/textures/nsfw.xpm", e);
}
