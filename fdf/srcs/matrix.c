/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:37:50 by flefebvr          #+#    #+#             */
/*   Updated: 2016/03/03 18:16:59 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_calc_matrix(t_fdfpoint *tp, t_fdfmatrix *m, t_fdfenv *e)
{
	double tx;
	double ty;
	double tz;

	tp->x -= e->center[0];
	tp->y -= e->center[1];
	tx = tp->x * m->m_x[0] + tp->y * m->m_x[1] + tp->z * m->m_x[2] + m->m_x[3];
	ty = tp->x * m->m_y[0] + tp->y * m->m_y[1] + tp->z * m->m_y[2] + m->m_y[3];
	tz = tp->x * m->m_z[0] + tp->y * m->m_z[1] + tp->z * m->m_z[2] + m->m_z[3];
	tp->x = tx + e->center[0];
	tp->y = ty + e->center[1];
	tp->z = tz;
}

static void	fdf_matrix_foreach(t_fdfmatrix *m, t_fdfenv *e)
{
	int x;
	int y;

	y = -1;
	while (++y < e->map->len)
	{
		x = -1;
		while (++x < (e->map->line[y]->len))
			fdf_calc_matrix(e->map->line[y]->point[x], m, e);
	}
}

void		fdf_rotation(t_fdfenv *e, double rad, char axis)
{
	t_fdfmatrix *m;

	if (!(m = (t_fdfmatrix *)ft_memalloc(sizeof(t_fdfmatrix))))
		ft_exit("Malloc failed", EXIT_FAILURE);
	if (axis == 'x')
	{
		m->m_y[2] = -sin(rad);
		m->m_z[1] = sin(rad);
	}
	if (axis == 'y')
	{
		m->m_x[2] = sin(rad);
		m->m_z[0] = -sin(rad);
	}
	if (axis == 'z')
	{
		m->m_x[1] = -sin(rad);
		m->m_y[0] = sin(rad);
	}
	m->m_x[0] = (axis == 'x' ? 1 : cos(rad));
	m->m_y[1] = (axis == 'y' ? 1 : cos(rad));
	m->m_z[2] = (axis == 'z' ? 1 : cos(rad));
	fdf_matrix_foreach(m, e);
	free(m);
}

void		fdf_translation(t_fdfenv *e, double x, double y)
{
	t_fdfmatrix *m;

	if (!(m = (t_fdfmatrix *)ft_memalloc(sizeof(t_fdfmatrix))))
		ft_exit("Malloc failed", EXIT_FAILURE);
	m->m_x[0] = 1;
	m->m_x[3] = x;
	m->m_y[1] = 1;
	m->m_y[3] = y;
	m->m_z[2] = 1;
	m->m_z[3] = 1;
	fdf_matrix_foreach(m, e);
	fdf_get_center(e);
	free(m);
}

void		fdf_zoom(t_fdfenv *e, double multiplier)
{
	t_fdfmatrix *m;

	if (!(m = (t_fdfmatrix *)ft_memalloc(sizeof(t_fdfmatrix))))
		ft_exit("Malloc failed", EXIT_FAILURE);
	m->m_x[0] = multiplier;
	m->m_y[1] = multiplier;
	m->m_z[2] = multiplier;
	fdf_matrix_foreach(m, e);
	fdf_get_center(e);
	free(m);
}
