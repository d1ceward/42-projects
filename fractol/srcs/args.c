/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 18:01:36 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/14 11:00:02 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	fol_isdigit(int ac, char **av, t_folenv *e)
{
	int	i;

	if (ac == 3)
	{
		if (ft_strlen(av[2]) == 0)
			return (0);
		i = -1;
		while (av[2][++i])
			if (ft_isdigit(av[2][i]) != 1)
				return (0);
		if ((e->iter_arg[1] = ft_atoi(av[2])) > 1000)
			return (0);
		e->iter_arg[0] = 1;
	}
	return (1);
}

void		fol_check_arg(int ac, char **av, t_folenv *e)
{
	char	*str;
	char	*str2;

	if ((ac < 2 || ac > 3) || fol_isdigit(ac, av, e) != 1
			|| (ft_strcmp("julia", av[1]) != 0
			&& ft_strcmp("mandelbrot", av[1]) != 0
			&& ft_strcmp("mandelbar", av[1]) != 0
			&& ft_strcmp("b_ship", av[1]) != 0
			&& ft_strcmp("celtic", av[1]) != 0
			&& ft_strcmp("buffalo", av[1]) != 0
			&& ft_strcmp("carpet", av[1]) != 0))
	{
		str = "usage: ./fractol [julia, mandelbrot, ";
		str2 = "mandelbar, b_ship, celtic, buffalo, carpet] [0-1000]";
		str = ft_strjoin(str, str2);
		ft_exit(str, EXIT_FAILURE);
	}
}

void		fol_get_fractal(char *name, t_folenv *e)
{
	if (ft_strcmp("julia", name) == 0)
		e->f = &(e->f_arr[0]);
	else if (ft_strcmp("mandelbrot", name) == 0)
		e->f = &(e->f_arr[1]);
	else if (ft_strcmp("mandelbar", name) == 0)
		e->f = &(e->f_arr[2]);
	else if (ft_strcmp("b_ship", name) == 0)
		e->f = &(e->f_arr[3]);
	else if (ft_strcmp("celtic", name) == 0)
		e->f = &(e->f_arr[4]);
	else if (ft_strcmp("buffalo", name) == 0)
		e->f = &(e->f_arr[5]);
	else if (ft_strcmp("carpet", name) == 0)
		e->f = &(e->f_arr[6]);
}
