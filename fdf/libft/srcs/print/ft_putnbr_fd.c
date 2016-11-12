/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 10:54:18 by flefebvr          #+#    #+#             */
/*   Updated: 2016/02/12 09:54:32 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = 0;
	if (n >= 0)
	{
		if (n >= 10)
			i += ft_putnbr_fd((n / 10), fd);
		i += ft_putchar_fd((n % 10 + '0'), fd);
	}
	else
	{
		i += ft_putchar_fd('-', fd);
		i += ft_putnbr_fd((-n), fd);
	}
	return (i);
}
