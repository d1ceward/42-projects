/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 07:38:56 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/15 16:46:10 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fol_mouse_button_hook(int button, int x, int y, t_folenv *e)
{
	if (button == MOUSE_WHEEL_UP || button == MOUSE_WHEEL_DOWN
		|| button == MOUSE_LEFT_CLICK || button == MOUSE_RIGHT_CLICK)
	{
		e->f->x += ((double)x - e->win_h / 2) / e->win_w / e->f->zoom;
		e->f->y += ((double)y - e->win_w / 2) / e->win_h / e->f->zoom;
	}
	if (button == MOUSE_WHEEL_UP || button == MOUSE_LEFT_CLICK)
	{
		e->f->zoom *= 1.1;
		e->f->zoom_ratio++;
	}
	else if (button == MOUSE_WHEEL_DOWN || button == MOUSE_RIGHT_CLICK)
	{
		e->f->zoom /= 1.1;
		e->f->zoom_ratio--;
	}
	e->redraw = 1;
	return (0);
}

int	fol_mouse_hook(int x, int y, t_folenv *e)
{
	if (x >= 0 && y >= 0 && x <= e->win_w && y <= e->win_h)
	{
		if (e->f->func == fol_julia && e->motion == 1)
		{
			e->f->cr = (double)x / (e->win_w * 2);
			e->f->ci = (double)y / (e->win_h * 2);
			e->redraw = 1;
		}
	}
	return (0);
}
