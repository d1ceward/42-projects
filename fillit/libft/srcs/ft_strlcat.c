/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:47:03 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/01 23:38:38 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i])
		i++;
	j = i;
	i = 0;
	while (dest[i] && i < size)
		i++;
	j += (i < size) ? i : size;
	if ((int)(size - ft_strlen(dest) - 1) > 0)
		ft_strncat(dest, src, size - ft_strlen(dest) - 1);
	return (j);
}
