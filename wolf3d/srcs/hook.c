/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 01:39:43 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 18:50:05 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	w3d_loop_move(t_w3denv *e)
{
	if (e->k.move_forward == 1 && e->k.move_backward != 1)
	{
		if (!(e->m.map[(int)(e->p.pos[0] + e->p.dir[0] *
				(e->p.move_speed * 2.4))][(int)e->p.pos[1]]))
			e->p.pos[0] += e->p.dir[0] * e->p.move_speed;
		if (!(e->m.map[(int)e->p.pos[0]][(int)(e->p.pos[1] +
				e->p.dir[1] * (e->p.move_speed * 2.4))]))
			e->p.pos[1] += e->p.dir[1] * e->p.move_speed;
	}
	if (e->k.move_backward == 1 && e->k.move_forward != 1)
	{
		if (!(e->m.map[(int)(e->p.pos[0] - e->p.dir[0] *
				(e->p.move_speed * 2.4))][(int)e->p.pos[1]]))
			e->p.pos[0] -= e->p.dir[0] * e->p.move_speed;
		if (!(e->m.map[(int)e->p.pos[0]][(int)(e->p.pos[1] -
				e->p.dir[1] * (e->p.move_speed * 2.4))]))
			e->p.pos[1] -= e->p.dir[1] * e->p.move_speed;
	}
}

static void	w3d_loop_strafe(t_w3denv *e)
{
	if (e->k.move_right == 1 && e->k.move_left != 1)
	{
		if (!(e->m.map[(int)(e->p.pos[0] + e->r.plane[0] *
				(e->p.move_speed * 2.4))][(int)e->p.pos[1]]))
			e->p.pos[0] += e->r.plane[0] * e->p.move_speed;
		if (!(e->m.map[(int)e->p.pos[0]][(int)(e->p.pos[1] +
				e->r.plane[1] * (e->p.move_speed * 2.4))]))
			e->p.pos[1] += e->r.plane[1] * e->p.move_speed;
	}
	if (e->k.move_left == 1 && e->k.move_right != 1)
	{
		if (!(e->m.map[(int)(e->p.pos[0] - e->r.plane[0] *
				(e->p.move_speed * 2.4))][(int)e->p.pos[1]]))
			e->p.pos[0] -= e->r.plane[0] * e->p.move_speed;
		if (!(e->m.map[(int)e->p.pos[0]][(int)(e->p.pos[1] - e->r.plane[1] *
				(e->p.move_speed * 2.4))]))
			e->p.pos[1] -= e->r.plane[1] * e->p.move_speed;
	}
}

static void	w3d_loop_rotation(t_w3denv *e)
{
	e->p.olddir = e->p.dir[0];
	e->r.oldplane = e->r.plane[0];
	if (e->k.rot_right == 1 && e->k.rot_left != 1)
	{
		e->p.dir[0] = e->p.dir[0] * cos(-e->p.rot_speed) - e->p.dir[1] *
			sin(-e->p.rot_speed);
		e->p.dir[1] = e->p.olddir * sin(-e->p.rot_speed) + e->p.dir[1] *
			cos(-e->p.rot_speed);
		e->r.plane[0] = e->r.plane[0] * cos(-e->p.rot_speed) - e->r.plane[1] *
			sin(-e->p.rot_speed);
		e->r.plane[1] = e->r.oldplane * sin(-e->p.rot_speed) + e->r.plane[1] *
			cos(-e->p.rot_speed);
	}
	if (e->k.rot_left == 1 && e->k.rot_right != 1)
	{
		e->p.dir[0] = e->p.dir[0] * cos(e->p.rot_speed) - e->p.dir[1] *
			sin(e->p.rot_speed);
		e->p.dir[1] = e->p.olddir * sin(e->p.rot_speed) + e->p.dir[1] *
			cos(e->p.rot_speed);
		e->r.plane[0] = e->r.plane[0] * cos(e->p.rot_speed) - e->r.plane[1] *
			sin(e->p.rot_speed);
		e->r.plane[1] = e->r.oldplane * sin(e->p.rot_speed) + e->r.plane[1] *
			cos(e->p.rot_speed);
	}
}

int			w3d_loop_hook(t_w3denv *e)
{
	w3d_loop_move(e);
	w3d_loop_strafe(e);
	w3d_loop_rotation(e);
	w3d_draw(e);
	return (0);
}
