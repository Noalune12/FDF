#include "../include/fdf.h"

static int	hex_to_int(const char *hex_str)
{
	int		result;
	char	c;

	result = 0;
	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		hex_str += 2;
	while (*hex_str)
	{
		result *= 16;
		c = ft_toupper(*hex_str);
		if (c >= '0' && c <= '9')
			result += c - '0';
		else if (c >= 'A' && c <= 'F')
			result += c - 'A' + 10;
		else
			return (-1);
		hex_str++;
	}
	return (result);
}

static int	fill_color(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ',')
		i++;
	if (str[i])
		i++;
	else
		return (0);
	return (hex_to_int(&str[i]));
}

int	fill_map_var(char *line, t_map *map_row, int y, int fd)
{
	char	**split;
	size_t	i;

	split = ft_split(line, " \n");
	if (!split)
		return (error_handler_parsing(3, &fd));
	i = 0;
	while (split[i])
	{
		map_row[i].x = i;
		map_row[i].y = y;
		map_row[i].z = ft_atoi(split[i]);
		map_row[i].color = fill_color(split[i]);
		map_row[i].is_end_row = 0;
		i++;
	}
	map_row[i].x = -1;
	map_row[i].y = -1;
	map_row[i].z = -1;
	map_row[i].color = -1;
	map_row[i].is_end_row = 1;
	ft_free_double(split);
	return (0);
}

int	get_width(char *line, int fd)
{
	char	**split;
	size_t	i;
	int		x;

	x = 0;
	split = ft_split(line, " \n");
	if (!split)
		return (error_handler_parsing(3, &fd));
	i = 0;
	while (split[i])
	{
		x += 1;
		i++;
	}
	ft_free_double(split);
	return (x);
}

int	allocate_y(t_map ***map, t_params *params, int fd, char *line)
{
	int	y;

	y = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL && *line != '\n')
			y += 1;
		free(line);
	}
	close(fd);
	params->map_info.map_height = y;
	*map = malloc((y + 1) * sizeof(t_map *));
	if (!*map)
		return (error_handler_parsing(4, NULL));
	ft_bzero(*map, (y + 1) * sizeof(t_map *));
	(*map)[y] = NULL;
	return (0);
}
