/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:53:44 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/18 16:47:20 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	char	*str_new;

	if (s)
	{
		i = 0;
		while (s[i] && ft_isspace(s[i]))
			i++;
		j = ft_strlen(s) - 1;
		while (s[i] && ft_isspace(s[j]))
			j--;
		str_new = ft_strsub(s, i, j - i + 1);
		return (str_new);
	}
	return (0);
}
