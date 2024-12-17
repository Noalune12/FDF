#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "./minilibx/mlx.h"
# include <math.h>
# include <errno.h>
# include "libft/libft.h"
# include "libft/gnl/get_next_line.h"
# define WIDTH 1000
# define HEIGHT 1000
# define ESC 65307
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define A_KEY 97
# define D_KEY 100
# define R_KEY 114
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define LEFT_CLICK 1
# define RIGHT_CLICK 3
# define ANGLE 0.52359877559

typedef struct s_map
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		is_end_row;
}	t_map;

typedef struct s_info
{
	int		map_width;
	int		map_height;
	float	z_min;
	float	z_max;
}	t_info;

typedef struct s_point
{
	int	iso_x;
	int	iso_y;
}	t_point;

typedef struct s_draw
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_draw;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_h_z
{
	int	total_gap;
	int	count;
	int	gap;
}	t_h_z;

typedef struct s_params
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	float	scale;
	float	angle;
	int		shift_x;
	int		shift_y;
	float	h_z;
	t_map	**map;
	t_image	img;
	t_info	map_info;
}	t_params;

void	ft_free_double(char **strs);
void	ft_free_t_map(t_map **map);
int		ft_free_line(char *line);

int		error_handler_parsing(int error_code, int *fd);
int		error_handler_param(int error_code, t_params *params);

int		parse_map(t_map ***map, t_params *params, char *file);
int		get_width(char *line, int fd);
int		allocate_y(t_map ***map, t_params *params, int fd, char *line);
int		fill_map_var(char *line, t_map *map_row, int y, int fd);

int		init_params(t_params *params, t_map **map);
float	calculate_scale(t_params *params);
void	calculate_shift_x(t_params *params);
void	calculate_shift_y(t_params *params);
void	adjust_z_scale(t_params *params);

void	draw_map_iso(t_map **map, t_params *params);
void	draw_line(t_point p0, t_point p1, int color, t_params params);
t_point	calculate_isometric(t_map point, t_params params);

int		handle_close(t_params *params);
int		handle_key(int keycode, t_params *params);
int		handle_mouse(int button, int x, int y, t_params *params);

#endif
