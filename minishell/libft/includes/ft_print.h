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
int		ft_putnstr(char const *s, size_t len);
int		ft_putnstr_fd(char const *s, size_t len, int fd);
void	ft_putwchar(wchar_t c);
void	ft_putwchar_fd(wchar_t c, int fd);
void	ft_putwstr(wchar_t const *wstr);
void	ft_putwstr_fd(wchar_t const *wstr, int fd);
void	ft_putnwstr(const wchar_t *wstr, size_t len);
void	ft_putnwstr_fd(const wchar_t *wstr, size_t len, int fd);
void	ft_putnbrbase(uintmax_t n, char *base);
void	ft_putnbrbase_fd(uintmax_t n, char *base, int fd);

#endif
