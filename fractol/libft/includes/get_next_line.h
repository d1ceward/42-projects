/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 12:26:04 by flefebvr          #+#    #+#             */
/*   Updated: 2016/02/12 15:24:24 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8
# define MAX_FD 256

typedef struct	s_gnlstore
{
	char	*cache[MAX_FD + 1];
	char	*buff;
	int		rbytes;
	char	*tmp;
}				t_gnlstore;

int				get_next_line(int const fd, char **line);

#endif
