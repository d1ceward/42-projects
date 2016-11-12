/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:50:50 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/04 18:00:38 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!*s2)
		return ((char *)s1);
	i = ft_strlen(s2);
	while (*s1 && n-- >= i)
	{
		if (*s1 == *s2 && ft_memcmp(s1, s2, i) == 0)
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
