/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_release.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 07:18:17 by flefebvr          #+#    #+#             */
/*   Updated: 2016/03/19 07:18:20 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fol_release_zoom_iter(int keycode, t_folenv *e)
{
	if (keycode == KEY_R)
		e->k.zoom_in = 0;
	if (keycode == KEY_F)
		e->k.zoom_out = 0;
	if (keycode == KEY_PLUS)
		e->k.more_iter = 0;
	if (keycode == KEY_MINUS)
		e->k.less_iter = 0;
}

static void	fol_release_translation(int keycode, t_folenv *e)
{
	if (keycode == KEY_W)
		e->k.trans_m_y = 0;
	if (keycode == KEY_S)
		e->k.trans_l_y = 0;
	if (keycode == KEY_A)
		e->k.trans_m_x = 0;
	if (keycode == KEY_D)
		e->k.trans_l_x = 0;
}

int			fol_keyrelease_hook(int keycode, t_folenv *e)
{
	fol_release_zoom_iter(keycode, e);
	fol_release_translation(keycode, e);
	return (0);
}
