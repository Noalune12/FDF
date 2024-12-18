/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:12:42 by lbuisson          #+#    #+#             */
/*   Updated: 2024/12/18 07:38:44 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <fcntl.h>

int	fill_map_loop(t_map ***map, t_params *params, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < params->map_info.map_height)
	{
		line = get_next_line(fd);
		if (!line || *line == '\n')
		{
			free(line);
			break ;
		}
		(*map)[i] = malloc((params->map_info.map_width + 1) * sizeof(t_map));
		if (!(*map)[i])
		{
			free(line);
			return (error_handler_parsing(4, NULL));
		}
		if (fill_map_var(line, (*map)[i], i, params->map_info.map_width) == -1)
			return (ft_free_line(line));
		free(line);
	}
	return (0);
}

static int	fill_map(t_map ***map, t_params *params, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_handler_parsing(1, NULL));
	if (fill_map_loop(map, params, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	allocate_map(t_map ***map, t_params *params, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_handler_parsing(1, NULL));
	line = get_next_line(fd);
	if (!line)
		return (error_handler_parsing(2, &fd));
	params->map_info.map_width = get_width(line, fd);
	if (params->map_info.map_width == -1)
	{
		free(line);
		close(fd);
		return (-1);
	}
	free(line);
	if (allocate_y(map, params, fd, line) == -1)
		return (-1);
	return (0);
}

static int	check_file_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 5 || file[i - 1] != 'f' || file[i - 2] != 'd' || file[i - 3] != 'f'
		|| file[i - 4] != '.')
		return (-1);
	return (0);
}

int	parse_map(t_map ***map, t_params *params, char *file)
{
	if (check_file_name(file) == -1)
		return (error_handler_parsing(0, NULL));
	if (allocate_map(map, params, file) == -1)
		return (-1);
	if (fill_map(map, params, file) == -1)
	{
		ft_free_t_map(*map);
		return (-1);
	}
	if (check_map(*map, params) == -1)
	{
		ft_free_t_map(*map);
		return (-1);
	}
	return (0);
}
