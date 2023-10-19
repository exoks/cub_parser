/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/19 12:29:42 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char	**parser(char *file)
{
	char	**map;
	int		fd;
	char		c;


	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	printf("fd => %d\n", fd);
	while(read(fd, &c, 1))
		printf("%c", c);
	close(fd);
	printf("\nfd => %d\n", fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (read(fd, &c, 1))
		printf("%c", c);
	printf("\n");
	return (map);
}

