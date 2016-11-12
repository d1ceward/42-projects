/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 17:27:32 by flefebvr          #+#    #+#             */
/*   Updated: 2016/01/05 17:30:58 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	init_map(t_store *store)
{
	int i;

	if (!(MAP = (char **)ft_memalloc(sizeof(char *) * ARRAY_SIZE)))
		ft_exit("error");
	i = 0;
	while (i < ARRAY_SIZE)
	{
		if (!(MAP[i] = (char *)ft_memalloc((sizeof(char) * ARRAY_SIZE) + 1)))
			ft_exit("error");
		i++;
	}
}

static void	init_tetri_pos(t_store *store)
{
	int i;

	if (!(TETRI_POS = (int **)ft_memalloc(sizeof(int *) * NB_TETRI)))
		ft_exit("error");
	i = 0;
	while (i < NB_TETRI)
	{
		if (!(TETRI_POS[i] = (int *)ft_memalloc(sizeof(int) * 2)))
			ft_exit("error");
		i++;
	}
}

static void	init_first_sharp_pos(t_store *store)
{
	int i;

	if (!(SHARP_POS = (int **)ft_memalloc(sizeof(int *) * NB_TETRI)))
		ft_exit("error");
	i = 0;
	while (i < NB_TETRI)
	{
		if (!(SHARP_POS[i] = (int *)ft_memalloc(sizeof(int) * 2)))
			ft_exit("error");
		i++;
	}
}

void		global_init(t_store *store)
{
	int i;

	if (!(TETRI_ARRAY = (char ***)ft_memalloc(sizeof(char *) * NB_TETRI)))
		ft_exit("error");
	i = 0;
	while (i < NB_TETRI)
	{
		if (!(TETRI_ARRAY[i] = (char **)ft_memalloc(sizeof(char *) * 4)))
			ft_exit("error");
		TETRI_ARRAY[i][0] = ft_strsub(TMP_ARRAY_T[i * 4], 0, 4);
		TETRI_ARRAY[i][1] = ft_strsub(TMP_ARRAY_T[i * 4 + 1], 0, 4);
		TETRI_ARRAY[i][2] = ft_strsub(TMP_ARRAY_T[i * 4 + 2], 0, 4);
		TETRI_ARRAY[i][3] = ft_strsub(TMP_ARRAY_T[i * 4 + 3], 0, 4);
		i++;
	}
	free(TMP_ARRAY_T);
	init_map(store);
	init_tetri_pos(store);
	init_first_sharp_pos(store);
}
