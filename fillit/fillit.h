/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 17:35:41 by flefebvr          #+#    #+#             */
/*   Updated: 2016/01/05 17:46:29 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"

# define BUFF_SIZE 545
# define TMP_ARRAY_T store->tmp_array_tetri
# define TETRI_ARRAY store->tetri_array
# define MAP store->map
# define NB_TETRI store->nb_tetri
# define ARRAY_SIZE 104
# define MAP_SIZE store->map_size
# define TETRI_POS store->tetri_pos
# define TETRI_Y(i) store->tetri_pos[i][0]
# define TETRI_X(i) store->tetri_pos[i][1]
# define SHARP_POS store->sharp_pos
# define TETRI_SY(i) store->sharp_pos[i][0]
# define TETRI_SX(i) store->sharp_pos[i][1]
# define TMP_Y store->tmp_y
# define TMP_X store->tmp_x
# define Y store->y
# define X store->x

typedef struct	s_store
{
	char	**tmp_array_tetri;
	int		nb_tetri;
	char	***tetri_array;
	int		y;
	int		x;
	int		**tetri_pos;
	int		**sharp_pos;
	int		map_size;
	char	**map;
	int		tmp_y;
	int		tmp_x;
}				t_store;

void			global_init(t_store *store);
void			check_composition(t_store *store, char *buff);
void			solver(t_store *store, int current);
void			print_map(t_store *store);
void			check_carriage_return(t_store *store, char *buff);

#endif
