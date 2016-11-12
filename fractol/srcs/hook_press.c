/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 07:12:06 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/14 10:23:50 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fol_press_zoom_iter(int keycode, t_folenv *e)
{
	if (keycode == KEY_R)
		e->k.zoom_in = 1;
	if (keycode == KEY_F)
		e->k.zoom_out = 1;
	if (keycode == KEY_PLUS)
		e->k.more_iter = 1;
	if (keycode == KEY_MINUS)
		e->k.less_iter = 1;
}

static void	fol_press_translation(int keycode, t_folenv *e)
{
	if (keycode == KEY_W)
		e->k.trans_m_y = 1;
	if (keycode == KEY_S)
		e->k.trans_l_y = 1;
	if (keycode == KEY_A)
		e->k.trans_m_x = 1;
	if (keycode == KEY_D)
		e->k.trans_l_x = 1;
}

static void	fol_press_fract_selector(int keycode, t_folenv *e)
{
	if (keycode == KEYPAD_1 || keycode == KEYPAD_2 || keycode == KEYPAD_3 ||
			keycode == KEYPAD_4 || keycode == KEYPAD_5 || keycode == KEYPAD_6 ||
			keycode == KEYPAD_7)
	{
		if (keycode == KEYPAD_1)
			e->f = &(e->f_arr[0]);
		if (keycode == KEYPAD_2)
			e->f = &(e->f_arr[1]);
		if (keycode == KEYPAD_3)
			e->f = &(e->f_arr[2]);
		if (keycode == KEYPAD_4)
			e->f = &(e->f_arr[3]);
		if (keycode == KEYPAD_5)
			e->f = &(e->f_arr[4]);
		if (keycode == KEYPAD_6)
			e->f = &(e->f_arr[5]);
		if (keycode == KEYPAD_7)
			e->f = &(e->f_arr[6]);
		e->redraw = 1;
	}
}

static void	fol_press_color_selector(int keycode, t_folenv *e)
{
	if (keycode == KEY_C)
	{
		if (e->sw_color > 5)
			e->sw_color = 0;
		else
			e->sw_color++;
		e->redraw = 1;
	}
}

int			fol_keypress_hook(int keycode, t_folenv *e)
{
	if (keycode == KEY_ESC)
		ft_exit("See you next time !", EXIT_SUCCESS);
	if (keycode == KEY_SPACE && e->f->func == fol_julia)
		e->motion = e->motion == 1 ? 0 : 1;
	if (keycode == KEY_F1)
	{
		e->helper = e->helper == 1 ? 0 : 1;
		e->redraw = 1;
	}
	if (keycode == KEY_DELETE)
	{
		fol_set_fractal(e);
		e->redraw = 1;
	}
	fol_press_zoom_iter(keycode, e);
	fol_press_translation(keycode, e);
	fol_press_fract_selector(keycode, e);
	fol_press_color_selector(keycode, e);
	return (0);
}
