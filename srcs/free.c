#include "../include/fdf.h"

int	ft_free_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (-1);
}

void	ft_free_double(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free (strs);
		strs = NULL;
	}
}

void	ft_free_t_map(t_map **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}
