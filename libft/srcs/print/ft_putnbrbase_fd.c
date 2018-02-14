/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 10:42:46 by flefebvr          #+#    #+#             */
/*   Updated: 2017/03/29 10:42:47 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	inner(uintmax_t n, char *base, size_t len, int fd)
{
	if (n >= len)
	{
		inner(n / len, base, len, fd);
		inner(n % len, base, len, fd);
	}
	else
		ft_putchar_fd(base[n], fd);
}

void		ft_putnbrbase_fd(uintmax_t n, char *base, int fd)
{
	inner(n, base, ft_strlen(base), fd);
}
