/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 04:35:34 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/15 16:48:56 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include "libft.h"

# define WIN_SIZE_W 729
# define WIN_SIZE_H 729

# define EXPOSE 12
# define EXPOSUREMASK (1L<<15)
# define KEYPRESS 2
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASE 3
# define KEYRELEASEMASK (1L<<1)
# define BUTTONPRESS 4
# define BUTTONPRESSMASK (1L<<2)
# define BUTTONRELEASE 5
# define BUTTONRELEASEMASK (1L<<3)
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK (1L<<6)

# define KEY_F1 65470
# define KEY_ESC 65307
# define KEY_SPACE 32
# define KEY_DELETE 65288
# define KEY_R 114
# define KEY_F 102
# define KEY_C 99
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 2
# define KEY_W 122
# define KEY_S 115
# define KEY_A 113
# define KEY_D 100
# define KEYPAD_1 65436
# define KEYPAD_2 65433
# define KEYPAD_3 65435
# define KEYPAD_4 65430
# define KEYPAD_5 65437
# define KEYPAD_6 65432
# define KEYPAD_7 65429

typedef struct	s_folkey
{
	int zoom_in;
	int zoom_out;
	int	more_iter;
	int less_iter;
	int trans_m_x;
	int trans_l_x;
	int trans_m_y;
	int trans_l_y;
}				t_folkey;

typedef struct	s_folfract
{
	char	*name;
	double	cr;
	double	ci;
	double	zr;
	double	zi;
	double	x;
	double	y;
	double	zoom;
	int		zoom_ratio;
	int		iter;
	int		iter_max;
	void	*func;
	int		info;
}				t_folfract;

typedef struct	s_folenv
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			sline;
	int			ed;
	int			win_w;
	int			win_h;
	t_folfract	*f_arr;
	t_folfract	*f;
	double		coord[2];
	t_folkey	k;
	int			redraw;
	int			motion;
	int			helper;
	int			iter_arg[2];
	int			sw_color;
	int			rgb[3];
	int			tmp;
}				t_folenv;

void			fol_check_arg(int ac, char **av, t_folenv *e);
void			fol_get_fractal(char *name, t_folenv *e);
int				fol_keypress_hook(int keycode, t_folenv *e);
int				fol_keyrelease_hook(int keycode, t_folenv *e);
int				fol_mouse_hook(int x, int y, t_folenv *e);
int				fol_mouse_button_hook(int button, int x, int y, t_folenv *e);
int				fol_loop_hook(t_folenv *e);
int				fol_expose_hook(t_folenv *e);
void			fol_draw(t_folenv *e);
void			fol_set_fractal(t_folenv *e);
void			fol_print_controls(void);
int				fol_get_color(int iter, t_folenv *e);
int				fol_julia(t_folenv *e, t_folfract f);
int				fol_mandelbrot(t_folenv *e, t_folfract f);
int				fol_mandelbar(t_folenv *e, t_folfract f);
int				fol_b_ship(t_folenv *e, t_folfract f);
int				fol_carpet(t_folenv *e, t_folfract f);
int				fol_celtic(t_folenv *e, t_folfract f);
int				fol_buffalo(t_folenv *e, t_folfract f);

#endif
