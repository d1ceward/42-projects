/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 04:35:12 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/15 16:49:59 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fol_set_fractal(t_folenv *e)
{
	e->f_arr[0] = (t_folfract){"Julia", 0.285, 0.01, 0, 0, 0, 0,
		1, 1, 0, (e->iter_arg[0] == 1 ? e->iter_arg[1] : 50), fol_julia, 1};
	e->f_arr[1] = (t_folfract){"Mandelbrot", 0, 0, 0, 0, 0, 0, 1,
		1, 0, (e->iter_arg[0] == 1 ? e->iter_arg[1] : 50), fol_mandelbrot, 1};
	e->f_arr[2] = (t_folfract){"Mandelbar", 0, 0, 0, 0, 0, 0,
		1, 1, 0, (e->iter_arg[0] == 1 ? e->iter_arg[1] : 50), fol_mandelbar, 1};
	e->f_arr[3] = (t_folfract){"Burning Ship", 0, 0, 0, 0, 0, 0,
		1, 1, 0, (e->iter_arg[0] == 1 ? e->iter_arg[1] : 50), fol_b_ship, 1};
	e->f_arr[4] = (t_folfract){"Celtic", 0, 0, 0, 0, 0, 0,
		1, 1, 0, (e->iter_arg[0] == 1 ? e->iter_arg[1] : 50), fol_celtic, 1};
	e->f_arr[5] = (t_folfract){"Buffalo", 0, 0, 0, 0, 0, 0,
		1, 1, 0, (e->iter_arg[0] == 1 ? e->iter_arg[1] : 50), fol_buffalo, 1};
	e->f_arr[6] = (t_folfract){"Carpet", 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, fol_carpet, 0};
}

static void	fol_init(t_folenv *e)
{
	e->helper = 1;
	e->win_h = WIN_SIZE_H;
	e->win_w = WIN_SIZE_W;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->win_w, e->win_h, "Fract'ol 42");
	if (!(e->f_arr = (t_folfract*)malloc(sizeof(t_folfract) * 7)))
		ft_exit("Malloc failed", EXIT_FAILURE);
	fol_set_fractal(e);
	fol_print_controls();
}

int			main(int ac, char **av)
{
	t_folenv	*e;

	if (!(e = (t_folenv*)ft_memalloc(sizeof(t_folenv))))
		ft_exit("Malloc failed", EXIT_FAILURE);
	fol_check_arg(ac, av, e);
	fol_init(e);
	fol_get_fractal(av[1], e);
	mlx_loop_hook(e->mlx, fol_loop_hook, e);
	mlx_hook(e->win, EXPOSE, EXPOSUREMASK, fol_expose_hook, e);
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, fol_keypress_hook, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASEMASK, fol_keyrelease_hook, e);
	mlx_hook(e->win, BUTTONPRESS, BUTTONPRESSMASK, fol_mouse_button_hook, e);
	mlx_hook(e->win, MOTIONNOTIFY, POINTERMOTIONMASK, fol_mouse_hook, e);
	mlx_loop(e->mlx);
	return (EXIT_SUCCESS);
}
