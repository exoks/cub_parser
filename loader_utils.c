/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/21 21:34:52 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size);

//==== get_next_line ===========================================================
char	*get_next_line(int fd, int index)
{
	char	*tmp;
	char	c;

	if (!read(fd, &c, 1) || c == '\n')
		return (ft_calloc((index + 1) * !(!index && c != '\n'), 1));
	tmp = get_next_line(fd, index + 1);
	if (tmp)
		tmp[index] = c;
	return (tmp);
}

//==== ft_calloc ===============================================================
void	*ft_calloc(size_t count, size_t size)
{
	void	*buff;
	int		i;

	if (count <= 0 || size <= 0)
		return (NULL);
	buff = malloc(count * size);
	if (!buff)
		return (NULL);
	i = -1;
	while (++i < (count * size))
		((char *) buff)[i] = 0;
	return (buff);
}

//==== create_rgb_color ========================================================
int32_t	create_rgb_color(int8_t r, int8_t g, int8_t b)
{
	return (r << 24 | g << 16 | b << 8);
}
