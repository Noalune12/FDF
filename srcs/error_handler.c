/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:12:23 by lbuisson          #+#    #+#             */
/*   Updated: 2024/12/18 07:39:09 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	error_handle_parsing_2(int error_code)
{
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
	if (error_code == 5)
	{
		errno = EINVAL;
		perror("Map is not a rectangle");
	}
	if (error_code == 6)
	{
		errno = EINVAL;
		perror("Map is empty");
	}
}

int	error_handler_parsing(int error_code, int *fd)
{
	if (fd)
		close(*fd);
	if (error_code == 0)
	{
		errno = EINVAL;
		perror("File is not .fdf");
	}
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
	error_handle_parsing_2(error_code);
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
