#include "../include/fdf.h"

void	bzero_params(t_params *params)
{
	params->mlx = NULL;
	params->win = NULL;
	params->width = 0;
	params->height = 0;
	params->scale = 0;
	params->angle = 0;
	params->h_z = 0;
	params->shift_x = 0;
	params->shift_y = 0;
	params->img.img = NULL;
	params->img.addr = NULL;
	params->img.bpp = 0;
	params->img.size_line = 0;
	params->img.endian = 0;
	params->map = NULL;
}

int	main(int argc, char **argv)
{
	t_map		**map;
	t_params	params;

	if (argc != 2)
	{
		errno = EINVAL;
		perror("2 arguments are required");
		exit(EXIT_FAILURE);
	}
	if (parse_map(&map, &params, argv[1]) == -1)
		exit(EXIT_FAILURE);
	bzero_params(&params);
	if (init_params(&params, map) == -1)
		exit(EXIT_FAILURE);
	draw_map_iso(map, &params);
	mlx_key_hook(params.win, handle_key, &params);
	mlx_hook(params.win, 17, 0, handle_close, &params);
	mlx_mouse_hook(params.win, handle_mouse, &params);
	mlx_loop(params.mlx);
	errno = 0;
	exit(EXIT_SUCCESS);
}
