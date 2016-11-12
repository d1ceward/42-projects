/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:15:19 by flefebvr          #+#    #+#             */
/*   Updated: 2016/01/22 20:10:03 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(int nb_arg, char **arg)
{
	char	*line;
	int		fd;
	int		code;

	if (nb_arg != 2)
		ft_exit("Error: Wrong argument number");
	if ((fd = open(arg[1], O_RDONLY)) == -1)
		ft_exit("Error: Can't open file");
	while ((code = get_next_line(fd, &line)) > 0)
	{
		printf("%d - |%s|\n", code, line);
		free(line);
	}
	printf("LAST %d - |%s|\n", code, line);
	return (0);
}
