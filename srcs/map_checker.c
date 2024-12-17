/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:12:38 by lbuisson          #+#    #+#             */
/*   Updated: 2024/12/17 17:13:50 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	check_map(t_map **map, t_params *params)
{
	int	i;
	int	j;

	i = 0;
	if (params->map_info.map_height == 0 || params->map_info.map_width == 0)
		return (error_handler_parsing(6, NULL));
	while (map[i])
	{
		j = 0;
		while (map[i][j].is_end_row != 1)
			j++;
		if (j != params->map_info.map_width)
			return (error_handler_parsing(5, NULL));
		i++;
	}
	return (1);
}
