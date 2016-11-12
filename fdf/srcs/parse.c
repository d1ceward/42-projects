/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:32:38 by flefebvr          #+#    #+#             */
/*   Updated: 2016/02/12 15:33:16 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_lines_checker(t_fdfenv *e, int len)
{
	if (e->prev_len != 0)
		if (e->prev_len != len)
			ft_exit("Found wrong line length. Exiting.", EXIT_FAILURE);
	e->prev_len = len;
}

static int	fdf_lines_counter(char *file)
{
	int		fd;
	int		nb_lines;
	char	buff;

	fd = 0;
	nb_lines = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_putstr("No file ");
		ft_exit(file, EXIT_FAILURE);
	}
	while (read(fd, &buff, 1) > 0)
		if (buff == '\n')
			nb_lines++;
	if (nb_lines == 0)
		ft_exit("No data found", EXIT_FAILURE);
	close(fd);
	return (nb_lines);
}

static int	fdf_get_coord(t_fdfenv *e, char *line, int nb_l, t_fdfpoint ***pt)
{
	char		**tmp;
	int			len;
	t_fdfpoint	*tmp_point;

	tmp = ft_strsplit(line, ' ');
	len = -1;
	while (tmp[++len] != NULL)
		;
	fdf_lines_checker(e, len);
	if (!((*pt) = (t_fdfpoint **)ft_memalloc(sizeof(t_fdfpoint) * len)))
		ft_exit("Malloc failed", EXIT_FAILURE);
	len = -1;
	while (tmp[++len] != NULL)
	{
		if (!(tmp_point = (t_fdfpoint *)ft_memalloc(sizeof(t_fdfpoint))))
			ft_exit("Malloc failed", EXIT_FAILURE);
		tmp_point->x = len * X_SIZE;
		tmp_point->y = nb_l * Y_SIZE;
		tmp_point->color = ft_atoi(tmp[len]);
		tmp_point->z = tmp_point->color * Z_SIZE;
		(*pt)[len] = tmp_point;
	}
	return (len);
}

void		fdf_get_lines(t_fdfenv *e, char **av, int fd)
{
	int			code;
	char		*line;
	int			i;
	t_fdfline	*tmp_line;
	t_fdfpoint	**tmp_point;

	i = fdf_lines_counter(av[1]);
	e->map->len = i;
	i++;
	if (!(e->map->line = (t_fdfline **)ft_memalloc(sizeof(t_fdfline) * i)))
		ft_exit("Malloc failed", EXIT_FAILURE);
	i = 0;
	while ((code = get_next_line(fd, &line)) > 0)
	{
		if (!(tmp_line = (t_fdfline *)ft_memalloc(sizeof(t_fdfline))))
			ft_exit("Malloc failed", EXIT_FAILURE);
		tmp_line->len = fdf_get_coord(e, line, i, &tmp_point);
		tmp_line->point = tmp_point;
		e->map->line[i] = tmp_line;
		i++;
	}
	e->map->len = i;
	if (code == -1)
		ft_exit("No data found", EXIT_FAILURE);
	close(fd);
}
