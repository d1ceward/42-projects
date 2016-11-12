/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 18:23:41 by flefebvr          #+#    #+#             */
/*   Updated: 2016/01/12 16:39:38 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		check_carriage_return(t_store *store, char *buff)
{
	int i;
	int j;

	i = 20;
	j = 0;
	while (((i - j) / 20) < NB_TETRI - 1)
	{
		if (!(ft_isspace(buff[i - 1])) || !(ft_isspace(buff[i])))
			ft_exit("error");
		i += 21;
		j++;
	}
}

static int	fillit_sqrt(int n)
{
	int i;

	i = 1;
	while (i * i < n)
		i++;
	return (i - 1);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		read_bytes;
	char	buff[BUFF_SIZE + 1];
	t_store	store;

	if (argc != 2)
		ft_exit("error");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_exit("error");
	if ((read_bytes = read(fd, buff, BUFF_SIZE)) == -1)
		ft_exit("error");
	buff[read_bytes] = '\0';
	if (close(fd) == -1)
		ft_exit("error");
	if (((read_bytes + 1) % 21) != 0 || ft_strstr(buff, "\n\n\n") != NULL ||
			buff[0] == '\n')
		ft_exit("error");
	if ((store.tmp_array_tetri = ft_strsplit(buff, '\n')) == NULL)
		ft_exit("error");
	check_composition(&store, buff);
	store.map_size = fillit_sqrt(store.nb_tetri * 4);
	while (++store.map_size)
		solver(&store, 0);
	return (0);
}
