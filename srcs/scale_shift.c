/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:12:48 by lbuisson          #+#    #+#             */
/*   Updated: 2024/12/17 17:12:48 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

float	calculate_scale(t_params *params)
{
	float	map_width_iso;
	float	map_height_iso;
	float	scale_x;
	float	scale_y;

	map_width_iso = (params->map_info.map_width + params->map_info.map_height);
	map_height_iso = (params->map_info.map_width + params->map_info.map_height);
	scale_x = params->width / map_width_iso;
	scale_y = params->height / map_height_iso;
	return (fmin(scale_x, scale_y));
}

static t_point	calculate_isometric_shift(t_map point, t_params params)
{
	t_point	iso_point;

	iso_point.iso_x = (point.x - point.y) * cos(params.angle);
	iso_point.iso_y = ((point.x + point.y) * sin(params.angle)
			- point.z * params.h_z);
	return (iso_point);
}

void	calculate_shift_x(t_params *params)
{
	int		min_x;
	int		max_x;
	int		i;
	int		j;
	t_point	iso_point;

	iso_point = calculate_isometric_shift(params->map[0][0], *params);
	min_x = iso_point.iso_x;
	max_x = iso_point.iso_x;
	i = -1;
	while (++i < params->map_info.map_height)
	{
		j = -1;
		while (++j < params->map_info.map_width)
		{
			iso_point = calculate_isometric_shift(params->map[i][j], *params);
			if (iso_point.iso_x < min_x)
				min_x = iso_point.iso_x;
			if (iso_point.iso_x > max_x)
				max_x = iso_point.iso_x;
		}
	}
	params->shift_x = (params->width - ((max_x - min_x) * params->scale)) / 2
		- (min_x * params->scale);
}

void	calculate_shift_y(t_params *params)
{
	int		min_y;
	int		max_y;
	int		i;
	int		j;
	t_point	iso_point;

	iso_point = calculate_isometric_shift(params->map[0][0], *params);
	min_y = iso_point.iso_y;
	max_y = iso_point.iso_y;
	i = -1;
	while (++i < params->map_info.map_height)
	{
		j = -1;
		while (++j < params->map_info.map_width)
		{
			iso_point = calculate_isometric_shift(params->map[i][j], *params);
			if (iso_point.iso_y < min_y)
				min_y = iso_point.iso_y;
			if (iso_point.iso_y > max_y)
				max_y = iso_point.iso_y;
		}
	}
	params->shift_y = (params->height - ((max_y - min_y) * params->scale)) / 2
		- (min_y * params->scale);
}
