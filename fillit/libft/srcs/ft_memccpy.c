/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:52:43 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/01 20:36:36 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*str;
	char	*str_src;

	i = 0;
	str = (char *)dest;
	str_src = (char *)src;
	while (i < n)
	{
		str[i] = str_src[i];
		if (c == str[i])
			return (str + i + 1);
		i++;
	}
	return (NULL);
}
