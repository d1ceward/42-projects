/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:31:19 by flefebvr          #+#    #+#             */
/*   Updated: 2016/03/04 15:40:51 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include "libft.h"

# define WIN_SIZE_W 1600
# define WIN_SIZE_H 900
# define KEYPRESS 2
# define KEYMASK 3
# define X_SIZE 20
# define Y_SIZE 20
# define Z_SIZE 10

# define MOVE_UP -100
# define MOVE_DOWN 100
# define MOVE_LEFT -100
# define MOVE_RIGHT 100
# define MOVE_ROT 1
# define ZOOM_X_IN 1.1
# define ZOOM_X_OUT 0.9

# define KEY_ESC 53
# define KEY_UP 15
# define KEY_DOWN 3
# define KEY_LEFT 6
# define KEY_RIGHT 7
# define KEY_ROT_X_M 13
# define KEY_ROT_X_L 1
# define KEY_ROT_Y_M 2
# define KEY_ROT_Y_L 0
# define KEY_ROT_Z_M 14
# define KEY_ROT_Z_L 12
# define KEY_ZOOM_IN 17
# define KEY_ZOOM_OUT 5

typedef struct	s_fdfpoint
{
	double	x;
	double	y;
	double	z;
	int		color;
}				t_fdfpoint;

typedef struct	s_fdfline
{
	t_fdfpoint	**point;
	int			len;
}				t_fdfline;

typedef struct	s_fdfmap
{
	t_fdfline	**line;
	int			len;
}				t_fdfmap;

typedef struct	s_fdfenv
{
	void		*mlx;
	void		*win;
	t_fdfmap	*map;
	double		center[2];
	void		*img;
	char		*img_data;
	int			s_line;
	int			bpp;
	int			ed;
	double		tmp;
	double		tmp2;
	double		abs_x;
	double		abs_y;
	int			prev_len;
}				t_fdfenv;

typedef struct	s_fdfmatrix {
	double m_x[4];
	double m_y[4];
	double m_z[4];
}				t_fdfmatrix;

void			fdf_get_lines(t_fdfenv *e, char **av, int fd);
int				fdf_get_color(t_fdfpoint *tp1, t_fdfpoint *tp2);
void			fdf_get_center(t_fdfenv *e);
int				fdf_point_out(t_fdfpoint *tp1);
int				fdf_key_hook(int keycode, t_fdfenv *e);
int				fdf_expose_hook(t_fdfenv *e);
void			fdf_draw(t_fdfenv *e);
void			fdf_rotation(t_fdfenv *e, double rad, char axis);
void			fdf_translation(t_fdfenv *e, double x, double y);
void			fdf_zoom(t_fdfenv *e, double multiplier);
void			fdf_print_controls(void);

#endif
