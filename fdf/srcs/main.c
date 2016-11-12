/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:30:46 by flefebvr          #+#    #+#             */
/*   Updated: 2016/03/04 17:29:06 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			fdf_get_color(t_fdfpoint *tp1, t_fdfpoint *tp2)
{
	int r_color;
	int tmp;

	r_color = 0xFFFF00;
	tmp = tp1->color > tp2->color ? tp1->color : tp2->color;
	while (tmp != 0)
	{
		if (tmp > 0)
		{
			if (r_color > 0xFF0B00)
				r_color -= 0x000B00;
			tmp--;
		}
		else
		{
			if (r_color > 0x0BFF00)
				r_color -= 0x0B0000;
			tmp++;
		}
	}
	return (r_color);
}

void		fdf_get_center(t_fdfenv *e)
{
	int	tmp_y;
	int	tmp_x;

	tmp_y = e->map->len;
	tmp_x = e->map->line[tmp_y - 1]->len;
	e->center[1] = (e->map->line[tmp_y - 1]->point[tmp_x - 1]->y +
		e->map->line[0]->point[0]->y) / 2;
	e->center[0] = (e->map->line[tmp_y - 1]->point[tmp_x - 1]->x +
		e->map->line[0]->point[0]->x) / 2;
}

int			fdf_point_out(t_fdfpoint *tp)
{
	if (tp->x > WIN_SIZE_W || tp->x <= 0 ||
		tp->y > WIN_SIZE_H || tp->y <= 0)
		return (0);
	else
		return (1);
}

static void	fdf_init(t_fdfenv *e)
{
	int width;
	int height;

	fdf_print_controls();
	width = WIN_SIZE_W;
	height = WIN_SIZE_H;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, width, height, "Wireframe 42");
	fdf_get_center(e);
	width = -e->center[0] + (width / 2);
	height = -e->center[1] + (height / 2);
	fdf_translation(e, width, height);
}

int			main(int ac, char **av)
{
	int			fd;
	t_fdfenv	*e;

	if (ac != 2)
		ft_exit("Usage: ./fdf <filename>", EXIT_FAILURE);
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		ft_putstr("No file ");
		ft_exit(av[1], EXIT_FAILURE);
	}
	if (!(e = (t_fdfenv *)malloc(sizeof(t_fdfenv))) ||
			!(e->map = (t_fdfmap*)malloc(sizeof(t_fdfmap))))
		ft_exit("Malloc failed", EXIT_FAILURE);
	e->prev_len = 0;
	fdf_get_lines(e, av, fd);
	if (e->map->line[0]->len == 0)
		ft_exit("No data found", EXIT_FAILURE);
	fdf_init(e);
	mlx_expose_hook(e->win, fdf_expose_hook, e);
	mlx_hook(e->win, KEYPRESS, KEYMASK, fdf_key_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
