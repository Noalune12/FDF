#include "fdf.h"

int	handle_close(t_params *params)
{
	mlx_destroy_image(params->mlx, params->img.img);
	mlx_destroy_window(params->mlx, params->win);
	mlx_destroy_display(params->mlx);
	free(params->mlx);
	ft_free_t_map(params->map);
	exit(0);
	return (0);
}

static int	handle_key_option(int keycode, t_params *params)
{
	if (keycode == ESC)
	{
		handle_close(params);
		exit(0);
	}
	else if (keycode == ARROW_LEFT)
		params->shift_x -= 10;
	else if (keycode == ARROW_RIGHT)
		params->shift_x += 10;
	else if (keycode == ARROW_UP)
		params->shift_y -= 10;
	else if (keycode == ARROW_DOWN)
		params->shift_y += 10;
	else if (keycode == A_KEY)
		params->angle = ANGLE;
	else if (keycode == D_KEY)
		params->angle = 0;
	else if (keycode == R_KEY)
		params->angle += 0.1;
	return (0);
}

int	handle_key(int keycode, t_params *params)
{
	handle_key_option(keycode, params);
	mlx_destroy_image(params->mlx, params->img.img);
	params->img.img = mlx_new_image(params->mlx, params->width, params->height);
	if (!params->img.img)
	{
		error_handler_param(3, params);
		exit(EXIT_FAILURE);
	}
	params->img.addr = mlx_get_data_addr(params->img.img, &params->img.bpp,
			&params->img.size_line, &params->img.endian);
	if (!params->img.addr)
	{
		error_handler_param(4, params);
		exit(EXIT_FAILURE);
	}
	mlx_clear_window(params->mlx, params->win);
	draw_map_iso(params->map, params);
	return (0);
}

static int	handle_mousse_option(int button, t_params *params)
{
	if (button == SCROLL_UP)
		params->scale *= 1.1;
	else if (button == SCROLL_DOWN)
		params->scale /= 1.1;
	else if (button == LEFT_CLICK)
		params->h_z += 0.05;
	else if (button == RIGHT_CLICK)
		params->h_z -= 0.05;
	return (0);
}

int	handle_mouse(int button, int x, int y, t_params *params)
{
	(void)x;
	(void)y;
	handle_mousse_option(button, params);
	mlx_destroy_image(params->mlx, params->img.img);
	params->img.img = mlx_new_image(params->mlx, params->width, params->height);
	if (!params->img.img)
	{
		error_handler_param(3, params);
		exit(EXIT_FAILURE);
	}
	params->img.addr = mlx_get_data_addr(params->img.img, &params->img.bpp,
			&params->img.size_line, &params->img.endian);
	if (!params->img.addr)
	{
		error_handler_param(4, params);
		exit(EXIT_FAILURE);
	}
	mlx_clear_window(params->mlx, params->win);
	draw_map_iso(params->map, params);
	return (0);
}
