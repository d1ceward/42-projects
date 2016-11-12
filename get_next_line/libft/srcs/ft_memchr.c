/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:52:57 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/01 22:47:41 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	test;
	unsigned char	*str;

	i = 0;
	test = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (str[i] == test)
			return (str + i);
		i++;
	}
	return (NULL);
}
