/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:38:14 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/15 16:47:36 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fol_celtic(t_folenv *e, t_folfract f)
{
	double	tmp;

	f.cr = (e->coord[1] - e->win_w / 2) / (f.zoom / 4 * e->win_w) + f.x;
	f.ci = (e->coord[0] - e->win_h / 2) / (f.zoom / 4 * e->win_h) + f.y;
	while ((f.zr * f.zr + f.zi * f.zi) < 4 && f.iter < f.iter_max)
	{
		tmp = f.zr;
		f.zr = fabs(f.zr * f.zr - f.zi * f.zi) + f.cr;
		f.zi = 2 * f.zi * tmp + f.ci;
		f.iter++;
	}
	return (f.iter);
}

int	fol_buffalo(t_folenv *e, t_folfract f)
{
	double	tmp;

	f.cr = (e->coord[1] - e->win_w / 2) / (f.zoom / 4 * e->win_w) + f.x;
	f.ci = (e->coord[0] - e->win_h / 2) / (f.zoom / 4 * e->win_h) + f.y;
	while ((f.zr * f.zr + f.zi * f.zi) < 4 && f.iter < f.iter_max)
	{
		tmp = f.zr;
		f.zr = fabs(f.zr * f.zr - f.zi * f.zi) + f.cr;
		f.zi = fabs(2 * f.zi * tmp) + f.ci;
		f.iter++;
	}
	return (f.iter);
}
