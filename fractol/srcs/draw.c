/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 03:46:41 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/14 11:04:03 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fol_print_controls(void)
{
	ft_putstr("========= \033[31;01mFRACT'OL 42\033[0m ========\n");
	ft_putstr("       \033[33;01mKey =>  Function\033[0m\n");
	ft_putstr("------------------------------\n");
	ft_putstr("======== \033[32;01mTRANSLATION\033[0m =========\n");
	ft_putstr("   W <-> S \033[30;01m=>\033[0m  Horizontal\n");
	ft_putstr("   A <-> D \033[30;01m=>\033[0m  Vertical\n");
	ft_putstr("======== \033[32;01mITER / ZOOM\033[0m =========\n");
	ft_putstr("   + <-> - \033[30;01m=>\033[0m  Iteration\n");
	ft_putstr("   R <-> F \033[30;01m=>\033[0m  Zoom\n");
	ft_putstr("----------- MOUSE ------------\n");
	ft_putstr("   Wheel   \033[30;01m=>\033[0m  Zoom\n");
	ft_putstr("========== \033[32;01mUTILITY\033[0m ===========\n");
	ft_putstr("   F1      \033[30;01m=>\033[0m  On/Off Info\n");
	ft_putstr("   Space   \033[30;01m=>\033[0m  On/Off Mouse\n");
	ft_putstr("   Delete  \033[30;01m=>\033[0m  Reset fractal\n");
	ft_putstr("   Keypad  \033[30;01m=>\033[0m  Change fractal\n");
	ft_putstr("   C       \033[30;01m=>\033[0m  Change color\n");
	ft_putstr("----------- MOUSE ------------\n");
	ft_putstr("   Motion  \033[30;01m=>\033[0m  Change Julia\n");
	ft_putstr("------------------------------\n");
}

static void	fol_point_to_img(int color, t_folenv *e)
{
	int		i;
	char	*rgb;

	i = e->coord[0] * e->sline + e->coord[1] * (e->bpp / 8);
	rgb = (char*)&color;
	e->img_data[i] = rgb[0];
	e->img_data[++i] = rgb[1];
	e->img_data[++i] = rgb[2];
}

static void	fol_calc_fractal(t_folenv *e, int (*func)(t_folenv*, t_folfract))
{
	int	iter;

	e->coord[0] = -1;
	while (++e->coord[0] < e->win_h)
	{
		e->coord[1] = -1;
		while (++e->coord[1] < e->win_w)
		{
			iter = (*func)(e, *e->f);
			fol_point_to_img(fol_get_color(iter, e), e);
		}
	}
}

static void	fol_helper(t_folenv *e)
{
	char	*str;
	char	*tmp;

	mlx_string_put(e->mlx, e->win, 10, 10, 0xFFFFFF, e->f->name);
	mlx_string_put(e->mlx, e->win, 10, 20, 0xFFFFFF, "------------");
	tmp = ft_itoa(e->f->iter_max);
	str = ft_strjoin("Iter max: ", tmp);
	ft_strdel(&tmp);
	if (e->f->info == 1)
		mlx_string_put(e->mlx, e->win, 10, 40, 0xFFFFFF, str);
	ft_strdel(&str);
	tmp = ft_itoa(e->f->zoom_ratio);
	str = ft_strjoin("Zoom: ", tmp);
	ft_strdel(&tmp);
	if (e->f->info == 1)
		mlx_string_put(e->mlx, e->win, 10, 60, 0xFFFFFF, str);
	ft_strdel(&str);
}

void		fol_draw(t_folenv *e)
{
	e->img = mlx_new_image(e->mlx, e->win_w, e->win_h);
	e->img_data = mlx_get_data_addr(e->img, &(e->bpp), &(e->sline), &(e->ed));
	fol_calc_fractal(e, e->f->func);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
	if (e->helper == 1)
		fol_helper(e);
}
