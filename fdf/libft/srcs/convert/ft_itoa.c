/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 10:51:56 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/18 17:01:18 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char		*str;
	size_t		len;

	len = ft_digit_count(n) + (n < 0);
	if (!(str = ft_strnew(len == 0 ? len + 1 : len)))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	else
	{
		if (n < 0)
			str[0] = '-';
		while (n)
		{
			str[len - 1] = '0' + ft_abs(n % 10);
			n = ft_abs(n / 10);
			len--;
		}
	}
	return (str);
}
