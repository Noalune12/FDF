#include "fdf.h"

int	error_handler_parsing(int error_code, int *fd)
{
	if (fd)
		close(*fd);
	if (error_code == 1)
	{
		errno = ENOENT;
		perror("File can't be opened");
	}
	if (error_code == 2)
	{
		errno = EINVAL;
		perror("No line to read");
	}
	if (error_code == 3)
	{
		errno = ENOMEM;
		perror("Split failed");
	}
	if (error_code == 4)
	{
		errno = ENOMEM;
		perror("Malloc failed");
	}
	errno = 0;
	return (-1);
}

static void	clean_all(t_params *params)
{
	if (params->img.img)
		mlx_destroy_image(params->mlx, params->img.img);
	if (params->win)
		mlx_destroy_window(params->mlx, params->win);
	if (params->mlx)
		mlx_destroy_display(params->mlx);
	if (params->mlx)
		free(params->mlx);
	if (params->map)
		ft_free_t_map(params->map);
}

int	error_handler_param(int error_code, t_params *params)
{
	if (error_code == 1)
	{
		errno = EFAULT;
		perror("mlx init failed");
	}
	if (error_code == 2)
	{
		errno = EFAULT;
		perror("mlx new window failed");
	}
	if (error_code == 3)
	{
		errno = EFAULT;
		perror("mlx new image failed");
	}
	if (error_code == 4)
	{
		errno = EFAULT;
		perror("mlx get data addr failed");
	}
	clean_all(params);
	errno = 0;
	return (-1);
}
