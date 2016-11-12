/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:52:22 by flefebvr          #+#    #+#             */
/*   Updated: 2015/11/30 15:21:03 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*str;

	if ((str = (void*)malloc(size)) && size)
	{
		ft_bzero(str, size);
		return (str);
	}
	return (NULL);
}
