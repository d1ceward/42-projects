/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:04:11 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/14 10:53:41 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fol_get_rgb(int red, int green, int blue, t_folenv *e)
{
	e->rgb[0] = (e->tmp / red) * e->f->iter_max;
	e->rgb[1] = (e->tmp / green) * e->f->iter_max;
	e->rgb[2] = (e->tmp / blue) * e->f->iter_max;
}

int			fol_get_color(int iter, t_folenv *e)
{
	if (e->f->func == fol_carpet)
		return (iter);
	if (iter == e->f->iter_max)
		return (0x000000);
	if (e->sw_color > 0)
	{
		e->tmp = iter;
		if (e->sw_color == 1)
			fol_get_rgb(2, 3, 4, e);
		if (e->sw_color == 2)
			fol_get_rgb(2, 4, 3, e);
		if (e->sw_color == 3)
			fol_get_rgb(3, 2, 4, e);
		if (e->sw_color == 4)
			fol_get_rgb(4, 2, 3, e);
		if (e->sw_color == 5)
			fol_get_rgb(4, 3, 2, e);
		if (e->sw_color == 6)
			fol_get_rgb(3, 4, 2, e);
		return ((e->rgb[0] << 16) + (e->rgb[1] << 8) + e->rgb[2]);
	}
	return ((iter * 255) / e->f->iter_max);
}
