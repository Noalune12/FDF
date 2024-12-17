#include "../include/fdf.h"

void	init_params_adjustment(t_params *params)
{
	params->width = WIDTH;
	params->height = HEIGHT;
	params->angle = 0.523599;
	adjust_z_scale(params);
	params->scale = calculate_scale(params);
	params->shift_x = 0;
	params->shift_y = 0;
	calculate_shift_x(params);
	calculate_shift_y(params);
}

int	init_params(t_params *params, t_map **map)
{
	params->map = map;
	params->mlx = mlx_init();
	if (!params->mlx)
		return (error_handler_param(1, params));
	params->win = mlx_new_window(params->mlx, WIDTH, HEIGHT, "Fdf");
	if (!params->win)
		return (error_handler_param(2, params));
	init_params_adjustment(params);
	params->img.img = mlx_new_image(params->mlx,
			params->width, params->height);
	if (!params->img.img)
		return (error_handler_param(3, params));
	params->img.addr = mlx_get_data_addr(params->img.img,
			&params->img.bpp, &params->img.size_line, &params->img.endian);
	if (!params->img.addr)
		return (error_handler_param(4, params));
	return (0);
}
