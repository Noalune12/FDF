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

static void	fill_end_of_row(t_map *map_row, int i)
{
	map_row[i].x = -1;
	map_row[i].y = -1;
	map_row[i].z = -1;
	map_row[i].color = -1;
	map_row[i].is_end_row = 1;
}

int	fill_map_var(char *line, t_map *map_row, int y, int width)
{
	char	**split;
	int		i;

	split = ft_split(line, " \n");
	if (!split)
		return (error_handler_parsing(3, NULL));
	i = 0;
	while (split[i])
	{
		if (i >= width)
		{
			ft_free_double(split);
			return (error_handler_parsing(5, NULL));
		}
		map_row[i].x = i;
		map_row[i].y = y;
		map_row[i].z = ft_atoi(split[i]);
		map_row[i].color = fill_color(split[i]);
		map_row[i].is_end_row = 0;
		i++;
	}
	fill_end_of_row(map_row, i);
	ft_free_double(split);
	return (0);
}
