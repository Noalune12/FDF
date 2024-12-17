/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_width_height.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:11:33 by lbuisson          #+#    #+#             */
/*   Updated: 2024/12/17 17:11:35 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
