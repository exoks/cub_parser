/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:54:27 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/22 00:58:43 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define	MAP	0
#define OTHER	1

//==============================================================================
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd, int index);
int32_t	get_rgb_color(int8_t r, int8_t g, int8_t b);
//==============================================================================
typedef struct s_data
{
	char	**map;
}		t_data;
//==============================================================================
t_data	*loader(char *file);
char	**parse_scene_file(int fd, int index, int area);
//==============================================================================
int		check_map_line(char *colom, int *area);
int		check_texture(char *line, int *area);
int		analize_line(char *line, int *area);
int		check_ceiling_floor_line(char *line, int *area);

//==== main ====================================================================
int	main(int ac, char **av)
{
	t_data	*data;

	data = loader(av[1]);
	return (EXIT_SUCCESS);
}

//==============================================================================
t_data	*loader(char *file)
{
	t_data	*data;
	int		fd;
	char	**lines;

	data = (t_data *) malloc(sizeof(t_data));
	fd = open(file, O_RDONLY);
	if (!data || fd < 0)
		return (free(data), NULL);
	lines = parse_scene_file(fd, 0, OTHER);
	if (!lines)
		return (printf("error\n"), NULL);
//	while (*lines)
//		printf("line => | %s\n", *(lines++));
	return (data);
}

//==== parse_===================================================================
char	**parse_scene_file(int fd, int index, int area)
{
	char	**map;
	char	*line;

	line = get_next_line(fd, 0);
	if (!line || !check_line(line, &area))
		return (ft_calloc((index + 1) * !line, sizeof(char *)));
	map = parse_scene_file(fd, index + 1, area);
	if (!map)
		return (free(line), NULL);
	map[index] = line;
	return (map);
}

//==== check_line ==============================================================
int	check_line(char *line, int *area)
{
	if (!line || (line && !*line && *area != MAP))
		return (1);
	else if (strstr(line, "NO") || strstr(line, "SO")
		|| strstr(line, "WE") || strstr(line, "EA"))
		return (check_texture(line, area));
	else if (strstr(line, "F") || strstr(line, "C"))
		return (check_ceiling_floor_line(line, area));
	else
		return (check_map_line(line, area));
}

//=== check_ceiling_floor_line ==================================================
int	check_ceiling_floor_line(char *line, int *area)
{
	int	prev_state;
	int	count;

	if (*area != OTHER)
		return (0);
	count = 0;
	prev_state = *line;
	while (*line)
	{
		if (prev_state == ',' && *line == ',')
			return (0);
		if (prev_state != ',' && *line == ',')
			count++;
		prev_state = *(line++);
	}
	return (count == 2);
}

//==== check_texture ===========================================================
int	check_texture(char *line, int *area)
{
	char	*tmp;

	if (*area != OTHER)
		return (0);
	tmp = strchr(line, '/');
	if (tmp && access(tmp + 1, F_OK | R_OK) == 0)
		return (1);
	return (0);
}

//==== is_valid ================================================================
int	check_map_line(char *colom, int *area)
{
	if (*colom != '1')
		return (0);
	while (*++colom)
	{
		if (!strchr("012NSWE", *colom))
			return (0);
		if (colom + 1 == NULL && *colom != '1')
			return (0);
	}
	*area = MAP;
	return (1);
}
