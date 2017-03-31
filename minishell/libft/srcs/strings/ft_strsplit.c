/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:52:33 by flefebvr          #+#    #+#             */
/*   Updated: 2015/12/07 18:18:29 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	tabsize(const char *s, char c)
{
	unsigned int	i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		nb++;
		while (s[i] == c)
			i++;
	}
	return (nb);
}

static unsigned int	wordsize(const char *s, char c)
{
	unsigned int	n;

	n = 0;
	while (s[n] != '\0' && s[n] != c)
		n++;
	return (n);
}

char				**ft_strsplit(const char *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;

	i = 0;
	j = 0;
	len = tabsize(s, c);
	if (!(s) || !(tab = (char**)malloc(sizeof(*tab) * (len + 1))))
		return (NULL);
	tab[len] = NULL;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		len = wordsize(&s[i], c);
		tab[j] = ft_strndup(&s[i], len);
		j++;
		i += len;
		while (s[i] == c)
			i++;
	}
	return (tab);
}
