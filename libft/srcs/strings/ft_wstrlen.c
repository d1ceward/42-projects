/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 10:41:35 by flefebvr          #+#    #+#             */
/*   Updated: 2017/03/29 10:42:00 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrlen(wchar_t *wstr)
{
	size_t len;

	len = 0;
	while (*wstr)
	{
		if (*wstr <= 0x7F)
			len++;
		else if (*wstr <= 0x7FF)
			len += 2;
		else if (*wstr <= 0xFFFF)
			len += 3;
		else if (*wstr <= 0x10FFFF)
			len += 4;
		wstr++;
	}
	return (len);
}
