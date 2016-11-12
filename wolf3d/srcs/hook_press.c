/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_press.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:58:10 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 21:42:29 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	w3d_keypress_movement(int keycode, t_w3denv *e)
{
	if (keycode == KEY_W)
		e->k.move_forward = 1;
	if (keycode == KEY_S)
		e->k.move_backward = 1;
	if (keycode == KEY_E)
		e->k.move_right = 1;
	if (keycode == KEY_Q)
		e->k.move_left = 1;
	if (keycode == KEY_D)
		e->k.rot_right = 1;
	if (keycode == KEY_A)
		e->k.rot_left = 1;
	if (keycode == KEY_SHIFT)
		e->k.run = 1;
}

int			w3d_keypress_hook(int keycode, t_w3denv *e)
{
	int	i;

	if (keycode == KEY_ESC)
		ft_exit("Wolf3d: See you next time !", EXIT_SUCCESS);
	if (keycode == KEY_F1)
		e->i.enable = (e->i.enable == 0 ? 1 : 0);
	if (keycode == KEY_F2)
		e->m.enable_tex = (e->m.enable_tex == 0 ? 1 : 0);
	if (keycode == KEY_F12)
		e->k.nsfw = (e->k.nsfw == 0 ? 1 : 0);
	if (keycode == KEY_SPACE)
	{
		i = -1;
		while (++i < e->m.nb_exits)
			if (e->i.pos[0] == e->m.e[i].pos[0] &&
					e->i.pos[1] == e->m.e[i].pos[1])
				w3d_level_swithcer(i, e);
	}
	if (keycode == KEY_DELETE)
		w3d_level_swithcer(-1, e);
	w3d_keypress_movement(keycode, e);
	return (0);
}
