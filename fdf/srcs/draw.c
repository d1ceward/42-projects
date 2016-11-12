/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:37:56 by flefebvr          #+#    #+#             */
/*   Updated: 2016/03/03 18:15:56 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fdf_print_controls(void)
{
	ft_putstr("======== \033[31;01mWIREFRAME 42\033[0m ========\n");
	ft_putstr("    \033[33;01mKey      =>  Function\033[0m\n");
	ft_putstr("------------------------------\n");
	ft_putstr("========== \033[32;01mROTATION\033[0m ==========\n");
	ft_putstr("    A <-> D  \033[30;01m=>\033[0m  Y Axis\n");
	ft_putstr("    W <-> S  \033[30;01m=>\033[0m  X Axis\n");
	ft_putstr("    Q <-> E  \033[30;01m=>\033[0m  Z Axis\n");
	ft_putstr("======== \033[32;01mTRANSLATION\033[0m =========\n");
	ft_putstr("    Z <-> X  \033[30;01m=>\033[0m  Horizontal\n");
	ft_putstr("    R <-> F  \033[30;01m=>\033[0m  Vertical\n");
	ft_putstr("=========== \033[32;01mZOOM\033[0m =============\n");
	ft_putstr("    T <-> G  \033[30;01m=>\033[0m  Zoom\n");
	ft_putstr("------------------------------\n");
}

static void	fdf_point_to_img(t_fdfpoint *tp, t_fdfenv *e, int color)
{
	int		i;
	char	*rgb;

	i = ((int)tp->x * (e->bpp / 8)) + ((int)tp->y * e->s_line);
	rgb = (char*)&color;
	e->img_data[i] = rgb[0];
	e->img_data[++i] = rgb[1];
	e->img_data[++i] = rgb[2];
}

static void	fdf_calc_line(t_fdfpoint tp1, t_fdfpoint tp2, t_fdfenv *e, int t)
{
	if (!fdf_point_out(&tp1) && !fdf_point_out(&tp2))
		return ;
	e->abs_x = fabs(tp1.x - tp2.x);
	e->abs_y = fabs(tp1.y - tp2.y);
	e->tmp = e->abs_x > e->abs_y ? e->abs_x : -e->abs_y;
	while (t == 1 && !((int)tp1.x == (int)tp2.x && (int)tp1.y == (int)tp2.y))
	{
		if (fdf_point_out(&tp1) == 1)
			fdf_point_to_img(&tp1, e, fdf_get_color(&tp1, &tp2));
		e->tmp2 = e->tmp;
		t = 0;
		if (e->tmp2 > -e->abs_x && (int)tp1.x != (int)tp2.x)
		{
			e->tmp -= e->abs_y;
			tp1.x += tp1.x < tp2.x ? 1 : -1;
			t = 1;
		}
		if (e->tmp2 < e->abs_y && (int)tp1.y != (int)tp2.y)
		{
			e->tmp += e->abs_x;
			tp1.y += tp1.y < tp2.y ? 1 : -1;
			t = 1;
		}
	}
}

static void	fdf_calc_map(t_fdfenv *e)
{
	t_fdfpoint	tmp;
	int			x;
	int			y;

	y = -1;
	while (++y < e->map->len)
	{
		x = -1;
		while (++x < e->map->line[y]->len)
		{
			tmp = *(e->map->line[y]->point[x]);
			if (e->map->line[y]->point[x + 1])
				fdf_calc_line(tmp, *(e->map->line[y]->point[x + 1]), e, 1);
			if (e->map->line[y + 1])
				if (e->map->line[y + 1]->point[x])
					fdf_calc_line(tmp, *(e->map->line[y + 1]->point[x]), e, 1);
		}
	}
}

void		fdf_draw(t_fdfenv *e)
{
	e->img = mlx_new_image(e->mlx, WIN_SIZE_W + 200, WIN_SIZE_H + 200);
	e->img_data = mlx_get_data_addr(e->img, &(e->bpp), &(e->s_line), &(e->ed));
	fdf_calc_map(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
}
