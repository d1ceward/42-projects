/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 12:25:43 by flefebvr          #+#    #+#             */
/*   Updated: 2016/01/27 19:44:56 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	gnl_counter(char *str)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		;
	return (i);
}

static void	gnl_reader(t_gnlstore *store, int fd)
{
	if (store->cache[fd] == NULL)
		store->cache[fd] = ft_strnew(1);
	while (!(ft_strchr(store->cache[fd], '\n'))
		&& (store->rbytes = read(fd, store->buff, BUFF_SIZE)) > 0)
	{
		store->buff[store->rbytes] = '\0';
		store->tmp = store->cache[fd];
		store->cache[fd] = ft_strjoin(store->tmp, store->buff);
		ft_strdel(&store->tmp);
	}
	ft_strdel(&store->buff);
}

int			get_next_line(int const fd, char **line)
{
	static t_gnlstore	store;

	if (fd < 0 || fd > MAX_FD || line == NULL ||
			!(store.buff = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	gnl_reader(&store, fd);
	if (store.rbytes == -1)
		return (-1);
	*line = ft_strsub(store.cache[fd], 0, gnl_counter(store.cache[fd]));
	if (ft_strchr(store.cache[fd], '\n'))
	{
		store.tmp = store.cache[fd];
		store.cache[fd] = ft_strdup(ft_strchr(store.tmp, '\n') + 1);
		ft_strdel(&store.tmp);
		return (1);
	}
	if (gnl_counter(store.cache[fd]) > 0)
	{
		store.cache[fd] = store.cache[fd] + gnl_counter(store.cache[fd]);
		return (1);
	}
	return (0);
}
