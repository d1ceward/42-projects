/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_release.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:58:36 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/26 16:22:21 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	w3d_keyrelease_movement(int keycode, t_w3denv *e)
{
	if (keycode == KEY_W)
		e->k.move_forward = 0;
	if (keycode == KEY_S)
		e->k.move_backward = 0;
	if (keycode == KEY_E)
		e->k.move_right = 0;
	if (keycode == KEY_Q)
		e->k.move_left = 0;
	if (keycode == KEY_D)
		e->k.rot_right = 0;
	if (keycode == KEY_A)
		e->k.rot_left = 0;
	if (keycode == KEY_SHIFT)
		e->k.run = 0;
}

int			w3d_keyrelease_hook(int keycode, t_w3denv *e)
{
	w3d_keyrelease_movement(keycode, e);
	return (0);
}
