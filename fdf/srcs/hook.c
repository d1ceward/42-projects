/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:29:38 by flefebvr          #+#    #+#             */
/*   Updated: 2016/02/12 15:32:57 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_key_hook_translation(int keycode, t_fdfenv *e)
{
	if (keycode == KEY_UP)
		fdf_translation(e, 0, MOVE_UP);
	else if (keycode == KEY_DOWN)
		fdf_translation(e, 0, MOVE_DOWN);
	else if (keycode == KEY_LEFT)
		fdf_translation(e, MOVE_LEFT, 0);
	else if (keycode == KEY_RIGHT)
		fdf_translation(e, MOVE_RIGHT, 0);
}

static void	fdf_key_hook_rotation(int keycode, t_fdfenv *e)
{
	double	plus;
	double	minus;

	plus = MOVE_ROT * (M_PI / 180);
	minus = -MOVE_ROT * (M_PI / 180);
	if (keycode == KEY_ROT_X_M)
		fdf_rotation(e, plus, 'x');
	else if (keycode == KEY_ROT_X_L)
		fdf_rotation(e, minus, 'x');
	else if (keycode == KEY_ROT_Y_M)
		fdf_rotation(e, plus, 'y');
	else if (keycode == KEY_ROT_Y_L)
		fdf_rotation(e, minus, 'y');
	else if (keycode == KEY_ROT_Z_M)
		fdf_rotation(e, plus, 'z');
	else if (keycode == KEY_ROT_Z_L)
		fdf_rotation(e, minus, 'z');
}

static void	fdf_key_hook_zoom(int keycode, t_fdfenv *e)
{
	if (keycode == KEY_ZOOM_IN)
		fdf_zoom(e, ZOOM_X_IN);
	else if (keycode == KEY_ZOOM_OUT)
		fdf_zoom(e, ZOOM_X_OUT);
}

int			fdf_key_hook(int keycode, t_fdfenv *e)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		ft_exit("See you next time !", EXIT_SUCCESS);
	}
	fdf_key_hook_translation(keycode, e);
	fdf_key_hook_rotation(keycode, e);
	fdf_key_hook_zoom(keycode, e);
	fdf_draw(e);
	return (0);
}

int			fdf_expose_hook(t_fdfenv *e)
{
	fdf_draw(e);
	return (0);
}
