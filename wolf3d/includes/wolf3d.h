/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 14:34:10 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/23 07:49:06 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx_code.h"

# define WIN_NAME "Wolf3D 42 by flefebvr"
# define WIN_W 1300
# define WIN_H 975
# define MAX_MAP_W 64
# define MAX_MAP_H 64
# define TEX_W 64
# define TEX_H 64
# define TEX_NB 24

typedef struct	s_w3dkey
{
	int	move_forward;
	int	move_backward;
	int	move_right;
	int	move_left;
	int	rot_right;
	int	rot_left;
	int run;
	int nsfw;
}				t_w3dkey;

typedef struct	s_w3dplayer
{
	double	move_speed;
	double	rot_speed;
	double	camera_x;
	double	pos[2];
	double	dir[2];
	int		hit;
	int		step[2];
	int		side;
	double	olddir;
}				t_w3dplayer;

typedef struct	s_w3dray
{
	double	plane[2];
	double	raypos[2];
	double	raydir[2];
	double	sidedist[2];
	double	deltadist[2];
	double	perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	oldplane;
	double	wallx;
	int		tex_x;
	int		tex_y;
	int		cur_col;
}				t_w3dray;

typedef struct	s_w3dtex
{
	void	*xpm;
	int		size[2];
	char	*img_data;
	int		bpp;
	int		sline;
	int		ed;
}				t_w3dtex;

typedef struct	s_w3ddoor
{
	int	pos[2];
	int	side;
}				t_w3ddoor;

typedef struct	s_w3dexit
{
	char	*level_name;
	int		pos[2];
}				t_w3dexit;

typedef struct	s_w3dmap
{
	int			**map;
	int			map_size[2];
	int			map_coord[2];
	int			enable_tex;
	int			color;
	int			nb_doors;
	t_w3ddoor	*d;
	int			texid;
	int			nb_exits;
	t_w3dexit	*e;
	char		*cur_level;
}				t_w3dmap;

typedef struct	s_w3dtime
{
	struct timeval	st;
	double			oldtime;
	double			time;
	double			frametime;
}				t_w3dtime;

typedef	struct	s_w3dinfo
{
	int			enable;
	int			pos[2];
	int			pos_y;
	t_w3dtime	ti;
}				t_w3dinfo;

typedef	struct	s_w3dparse
{
	int			fd;
	int			code_gnl;
	char		**str;
	int			size_s;
	int			size_sd;
	int			size_sde;
}				t_w3dparse;

typedef struct	s_w3denv
{
	t_w3dkey	k;
	t_w3dplayer	p;
	t_w3dray	r;
	t_w3dmap	m;
	t_w3dtex	**t;
	t_w3dinfo	i;
	t_w3dparse	pa;
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			sline;
	int			ed;
	int			nodraw;
}				t_w3denv;

void			w3d_parse(t_w3denv *e);
void			w3d_get_mapformat_value(t_w3denv *e);
void			w3d_parse_malloc(t_w3denv *e);
void			w3d_get_door(int i, char *line, t_w3denv *e);
void			w3d_get_exit(int i, char *line, t_w3denv *e);
void			w3d_load_tex(t_w3denv *e);
void			w3d_draw(t_w3denv *e);
void			w3d_raycasting(t_w3denv *e);
void			w3d_draw_base_walls(t_w3denv *e);
void			w3d_draw_tex_walls(t_w3denv *e);
void			w3d_draw_floor_ceiling(t_w3denv *e);
void			w3d_pixel_to_img(int y, t_w3denv *e);
int				w3d_loop_hook(t_w3denv *e);
int				w3d_keypress_hook(int keycode, t_w3denv *e);
void			w3d_level_swithcer(int i, t_w3denv *e);
int				w3d_keyrelease_hook(int keycode, t_w3denv *e);
void			w3d_parse_free(t_w3denv *e);

#endif
