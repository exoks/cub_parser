#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char	*parse_colom(int fd, int index);
char	**create_map(int fd, int index);
void	*ft_calloc(size_t count, size_t size);

int	main(int ac, char **av)
{
	char	**map;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	map = create_map(fd, 0);
	if (!map)
		return (printf("error"), EXIT_FAILURE);
	int i = -1;
	while(map[++i])
		printf(">>>>>>> %s\n", map[i]);
	return (EXIT_SUCCESS);
}

int	is_valid(char *colom)
{
	int	i;

	if (!colom)
		return (1);
	i = -1;
	if (colom[++i] != '1')
		return (0);
	while (colom[++i] && strchr("012", colom[i]))
		;
	return (!colom[i] && colom[i - 1] == '1');
}

char	**create_map(int fd, int index)
{
	char	**map;
	char	*colom;

	colom = parse_colom(fd, 0);
	if (!is_valid(colom))
		return (NULL);
	if (!colom)
		return (ft_calloc((index + 1) * (index > 2), sizeof(char *)));
	map = create_map(fd, index + 1);
	if (!map)
		return (free(colom), NULL);
	map[index] = colom;
	return (map);
}

char	*parse_colom(int fd, int index)
{
	char	*tmp;
	char	c;

	if (!read(fd, &c, 1) || c == '\n')
		return (ft_calloc((index + 1) * (index > 2), 1));
	tmp = parse_colom(fd, index + 1);
	if (tmp)
		tmp[index] = c;
	return (tmp);
}

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
