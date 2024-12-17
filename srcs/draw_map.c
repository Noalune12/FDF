#include "../include/fdf.h"

static void	assign_color(t_map map, int *color)
{
	if (map.color == 0)
		*color = 0x00FFFFFF;
	else
		*color = 0x00 + map.color;
}

static void	draw_map_loop(t_map **map, t_params *params, int i, int j)
{
	int		color;
	t_point	current_point;
	t_point	next_point;

	assign_color(map[i][j], &color);
	current_point = calculate_isometric(map[i][j], *params);
	if (map[i][j + 1].is_end_row != 1)
	{
		assign_color(map[i][j + 1], &color);
		next_point = calculate_isometric(map[i][j + 1], *params);
		draw_line(current_point, next_point, color, *params);
	}
	if (map[i + 1] && map[i + 1][j].is_end_row != 1)
	{
		assign_color(map[i + 1][j], &color);
		next_point = calculate_isometric(map[i + 1][j], *params);
		draw_line(current_point, next_point, color, *params);
	}
}

void	draw_map_iso(t_map **map, t_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].is_end_row != 1)
		{
			draw_map_loop(map, params, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(params->mlx, params->win, params->img.img, 0, 0);
}
