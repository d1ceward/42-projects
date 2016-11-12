/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 14:35:27 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/02 19:00:49 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	w3d_init(t_w3denv *e)
{
	if ((e->mlx = mlx_init()) == NULL)
		ft_exit("Wolf3d: mlx_init() failed", EXIT_FAILURE);
	if ((e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, WIN_NAME)) == NULL)
		ft_exit("Wolf3d: mlx_new_window() failed", EXIT_FAILURE);
	w3d_load_tex(e);
	if ((e->pa.fd = open("./map/level_01.w3dmf", O_RDONLY)) < 0)
		ft_exit("Wolf3d: Failed to open map file", EXIT_FAILURE);
	w3d_parse(e);
	close(e->pa.fd);
}

int			main(int ac, char **av)
{
	t_w3denv	*e;

	(void)av;
	if (ac != 1)
		ft_exit("Usage: ./wolf3d", EXIT_FAILURE);
	if ((e = (t_w3denv*)ft_memalloc(sizeof(t_w3denv))) == NULL)
		ft_exit("Wolf3d: Malloc failed", EXIT_FAILURE);
	w3d_init(e);
	mlx_loop_hook(e->mlx, w3d_loop_hook, e);
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, w3d_keypress_hook, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASEMASK, w3d_keyrelease_hook, e);
	mlx_loop(e->mlx);
	return (EXIT_SUCCESS);
}
