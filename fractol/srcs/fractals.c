/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 13:23:06 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/15 16:48:11 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fol_julia(t_folenv *e, t_folfract f)
{
	double	tmp;

	f.zr = (e->coord[1] - e->win_w / 2) / (f.zoom / 4 * e->win_w) + f.x;
	f.zi = (e->coord[0] - e->win_h / 2) / (f.zoom / 4 * e->win_h) + f.y;
	while ((f.zr * f.zr + f.zi * f.zi) < 4 && f.iter < f.iter_max)
	{
		tmp = f.zr;
		f.zr = f.zr * f.zr - f.zi * f.zi + f.cr;
		f.zi = 2 * f.zi * tmp + f.ci;
		f.iter++;
	}
	return (f.iter);
}

int	fol_mandelbrot(t_folenv *e, t_folfract f)
{
	double	tmp;

	f.cr = (e->coord[1] - e->win_w / 2) / (f.zoom / 4 * e->win_w) + f.x;
	f.ci = (e->coord[0] - e->win_h / 2) / (f.zoom / 4 * e->win_h) + f.y;
	while ((f.zr * f.zr + f.zi * f.zi) < 4 && f.iter < f.iter_max)
	{
		tmp = f.zr;
		f.zr = f.zr * f.zr - f.zi * f.zi + f.cr;
		f.zi = 2 * f.zi * tmp + f.ci;
		f.iter++;
	}
	return (f.iter);
}

int	fol_mandelbar(t_folenv *e, t_folfract f)
{
	double	tmp;

	f.cr = (e->coord[1] - e->win_w / 2) / (f.zoom / 4 * e->win_w) + f.x;
	f.ci = (e->coord[0] - e->win_h / 2) / (f.zoom / 4 * e->win_h) + f.y;
	while ((f.zr * f.zr + f.zi * f.zi) < 4 && f.iter < f.iter_max)
	{
		tmp = f.zr;
		f.zr = f.zr * f.zr - f.zi * f.zi + f.cr;
		f.zi = -2 * f.zi * tmp + f.ci;
		f.iter++;
	}
	return (f.iter);
}

int	fol_b_ship(t_folenv *e, t_folfract f)
{
	double	tmp;

	f.cr = (e->coord[1] - e->win_w / 2) / (f.zoom / 4 * e->win_w) + f.x;
	f.ci = (e->coord[0] - e->win_h / 2) / (f.zoom / 4 * e->win_h) + f.y;
	while ((f.zr * f.zr + f.zi * f.zi) < 4 && f.iter < f.iter_max)
	{
		tmp = f.zr;
		f.zr = f.zr * f.zr - f.zi * f.zi + f.cr;
		f.zi = fabs(2 * f.zi * tmp) + f.ci;
		f.iter++;
	}
	return (f.iter);
}

int	fol_carpet(t_folenv *e, t_folfract f)
{
	int y;
	int	x;

	(void)f;
	y = e->coord[0];
	x = e->coord[1];
	while ((y > 0 || x > 0))
	{
		if (y % 3 == 1 && x % 3 == 1)
			return (0x000000);
		y /= 3;
		x /= 3;
	}
	return (0x5E5E5E);
}
