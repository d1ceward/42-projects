/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:23:53 by flefebvr          #+#    #+#             */
/*   Updated: 2016/02/12 15:23:54 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

void	ft_exit(const char *str, int status);
int		ft_putchar(char c);
int		ft_putchar_fd(char c, int fd);
int		ft_putendl(char const *s);
int		ft_putendl_fd(char const *s, int fd);
int		ft_putnbr(int n);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr(char const *s);
int		ft_putstr_fd(char const *s, int fd);

#endif
