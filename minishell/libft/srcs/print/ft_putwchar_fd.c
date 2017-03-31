/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 18:04:37 by flefebvr          #+#    #+#             */
/*   Updated: 2016/05/20 18:04:38 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwchar_fd(wchar_t wc, int fd)
{
	if (wc <= 0x7F)
		ft_putchar_fd(wc, fd);
	else if (wc <= 0x7FF)
	{
		ft_putchar_fd((wc >> 6) + 0xC0, fd);
		ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
	else if (wc <= 0xFFFF)
	{
		ft_putchar_fd((wc >> 12) + 0xE0, fd);
		ft_putchar_fd(((wc >> 6) & 0x3F) + 0x80, fd);
		ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
	else if (wc <= 0x10FFFF)
	{
		ft_putchar_fd((wc >> 18) + 0xF0, fd);
		ft_putchar_fd(((wc >> 12) & 0x3F) + 0x80, fd);
		ft_putchar_fd(((wc >> 6) & 0x3F) + 0x80, fd);
		ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
}
