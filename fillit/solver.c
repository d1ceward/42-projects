/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 10:09:03 by flefebvr          #+#    #+#             */
/*   Updated: 2016/01/03 16:15:36 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	del_tetri(t_store *store, int current)
{
	int y;
	int x;

	y = -1;
	while (++y < MAP_SIZE)
	{
		x = -1;
		while (++x < MAP_SIZE)
		{
			if (MAP[y][x] == (current + 'A'))
				MAP[y][x] = '\0';
		}
	}
}

static int	add_tetri(t_store *store, int current)
{
	int y;
	int x;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			TMP_Y = (TETRI_Y(current) + y) - TETRI_SY(current);
			TMP_X = (TETRI_X(current) + x) - TETRI_SX(current);
			if (TETRI_ARRAY[current][y][x] == '#')
			{
				if (TMP_Y < 0 || TMP_Y >= MAP_SIZE || TMP_X < 0
						|| TMP_X >= MAP_SIZE || MAP[TMP_Y][TMP_X])
				{
					del_tetri(store, current);
					return (0);
				}
				MAP[TMP_Y][TMP_X] = current + 'A';
			}
		}
	}
	return (1);
}

void		solver(t_store *store, int current)
{
	TETRI_Y(current) = -1;
	while (++TETRI_Y(current) < MAP_SIZE)
	{
		TETRI_X(current) = -1;
		while (++TETRI_X(current) < MAP_SIZE)
		{
			if (add_tetri(store, current))
			{
				if ((current + 1) != NB_TETRI)
					solver(store, current + 1);
				else
					print_map(store);
				del_tetri(store, current);
			}
		}
	}
}
