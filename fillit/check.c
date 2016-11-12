/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 15:05:57 by flefebvr          #+#    #+#             */
/*   Updated: 2016/01/03 16:18:18 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	check_size_and_char(t_store *store)
{
	int	y;
	int x;

	y = -1;
	while (TMP_ARRAY_T[++y])
	{
		x = -1;
		while (TMP_ARRAY_T[y][++x])
		{
			if (TMP_ARRAY_T[y][x] != '#' && TMP_ARRAY_T[y][x] != '.')
				ft_exit("error");
		}
		if (x != 4)
			ft_exit("error");
	}
	if ((y % 4) != 0)
		ft_exit("error");
	if ((NB_TETRI = (y / 4)) > 26)
		ft_exit("error");
}

static void	check_sharp_number(t_store *store)
{
	int	y;
	int	x;
	int bloc;
	int count;

	y = 0;
	x = 0;
	count = 0;
	while (TMP_ARRAY_T[y])
	{
		bloc = -1;
		while (++bloc < 16)
		{
			if (TMP_ARRAY_T[y][x] == '#')
				count++;
			x++;
			if (((bloc + 1) % 4) == 0)
			{
				y++;
				x = 0;
			}
		}
		if ((count % 4) != 0)
			ft_exit("error");
	}
}

static void	check_adjacent_sharp(t_store *store, int i, int count)
{
	while (Y < 4)
	{
		while (X < 4)
		{
			if (Y >= 0 && X >= 0 && Y < 4 && (X + 1) < 4 &&
				TETRI_ARRAY[i][Y][X + 1] == '#' && TETRI_ARRAY[i][Y][X] == '#')
				count++;
			if (Y >= 0 && (X - 1) >= 0 && Y < 4 && X < 4 &&
				TETRI_ARRAY[i][Y][X - 1] == '#' && TETRI_ARRAY[i][Y][X] == '#')
				count++;
			if (Y >= 0 && X >= 0 && (Y + 1) < 4 && X < 4 &&
				TETRI_ARRAY[i][Y + 1][X] == '#' && TETRI_ARRAY[i][Y][X] == '#')
				count++;
			if ((Y - 1) >= 0 && X >= 0 && Y < 4 && X < 4 &&
				TETRI_ARRAY[i][Y - 1][X] == '#' && TETRI_ARRAY[i][Y][X] == '#')
				count++;
			X++;
		}
		X = 0;
		Y++;
	}
	if (count < 5)
		ft_exit("error");
}

static void	get_first_sharp(t_store *store, int i)
{
	Y = -1;
	while (++Y < 4)
	{
		X = -1;
		while (++X < 4)
			if (TETRI_ARRAY[i][Y][X] == '#')
				return ;
	}
}

void		check_composition(t_store *store, char *buff)
{
	int i;

	check_size_and_char(store);
	check_sharp_number(store);
	global_init(store);
	i = -1;
	while (++i < NB_TETRI)
	{
		get_first_sharp(store, i);
		TETRI_SY(i) = Y;
		TETRI_SX(i) = X;
		check_adjacent_sharp(store, i, 0);
	}
	check_carriage_return(store, buff);
}
