/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 03:46:47 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/15 16:50:22 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fol_do_iter(t_folenv *e)
{
	if (e->k.more_iter == 1)
	{
		e->f->iter_max++;
		e->redraw = 1;
	}
	if (e->k.less_iter == 1 && e->f->iter_max > 0)
	{
		e->f->iter_max--;
		e->redraw = 1;
	}
}

static void	fol_do_zoom(t_folenv *e)
{
	if (e->k.zoom_in == 1)
	{
		e->f->zoom *= 1.1;
		e->f->x += (e->win_h / 2) / e->win_w / e->f->zoom;
		e->f->y += (e->win_w / 2) / e->win_h / e->f->zoom;
		e->redraw = 1;
		e->f->zoom_ratio++;
	}
	if (e->k.zoom_out == 1)
	{
		e->f->zoom /= 1.1;
		e->f->x += (e->win_h / 2) / e->win_w / e->f->zoom;
		e->f->y += (e->win_w / 2) / e->win_h / e->f->zoom;
		e->redraw = 1;
		e->f->zoom_ratio--;
	}
}

static void	fol_do_translation(t_folenv *e)
{
	if (e->k.trans_m_y == 1)
	{
		e->f->y -= 0.05 / e->f->zoom;
		e->redraw = 1;
	}
	if (e->k.trans_l_y == 1)
	{
		e->f->y += 0.05 / e->f->zoom;
		e->redraw = 1;
	}
	if (e->k.trans_m_x == 1)
	{
		e->f->x -= 0.05 / e->f->zoom;
		e->redraw = 1;
	}
	if (e->k.trans_l_x == 1)
	{
		e->f->x += 0.05 / e->f->zoom;
		e->redraw = 1;
	}
}

int			fol_loop_hook(t_folenv *e)
{
	fol_do_iter(e);
	fol_do_zoom(e);
	fol_do_translation(e);
	if (e->redraw == 1)
	{
		fol_draw(e);
		e->redraw = 0;
	}
	return (0);
}

int			fol_expose_hook(t_folenv *e)
{
	fol_draw(e);
	return (0);
}
