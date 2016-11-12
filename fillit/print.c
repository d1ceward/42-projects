/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 13:09:29 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/30 09:26:26 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_map(t_store *store)
{
	int y;
	int x;

	free(TETRI_ARRAY);
	free(TETRI_POS);
	free(SHARP_POS);
	y = -1;
	while (++y < MAP_SIZE)
	{
		x = -1;
		while (++x < MAP_SIZE)
		{
			if (MAP[y][x])
				ft_putchar(MAP[y][x]);
			else
				ft_putchar('.');
		}
		ft_putchar('\n');
	}
	exit(1);
}
