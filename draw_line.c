#include "fdf.h"

t_point	calculate_isometric(t_map point, t_params params)
{
	t_point	iso_point;

	iso_point.iso_x = (point.x - point.y) * cos(params.angle) * params.scale;
	iso_point.iso_y = ((point.x + point.y) * sin(params.angle) - point.z
			* params.h_z) * params.scale;
	iso_point.iso_x = iso_point.iso_x + params.shift_x;
	iso_point.iso_y = iso_point.iso_y + params.shift_y;
	return (iso_point);
}

static void	put_pixel_to_image(t_image *img, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = (y * img->size_line + x * (img->bpp / 8));
		img->addr[pixel] = color;
		img->addr[pixel + 1] = (color >> 8);
		img->addr[pixel + 2] = (color >> 16);
		img->addr[pixel + 3] = (color >> 24);
	}
}

static void	init_draw(t_draw *draw, t_point p0, t_point p1)
{
	draw->dx = abs(p1.iso_x - p0.iso_x);
	draw->dy = abs(p1.iso_y - p0.iso_y);
	if (p0.iso_x < p1.iso_x)
		draw->sx = 1;
	else
		draw->sx = -1;
	if (p0.iso_y < p1.iso_y)
		draw->sy = 1;
	else
		draw->sy = -1;
	draw->err = draw->dx - draw->dy;
}

void	draw_line(t_point p0, t_point p1, int color, t_params params)
{
	t_draw	draw;

	init_draw(&draw, p0, p1);
	while (1)
	{
		put_pixel_to_image(&params.img, p0.iso_x, p0.iso_y, color);
		if (p0.iso_x == p1.iso_x && p0.iso_y == p1.iso_y)
			break ;
		draw.e2 = 2 * draw.err;
		if (draw.e2 > -draw.dy)
		{
			draw.err -= draw.dy;
			p0.iso_x += draw.sx;
		}
		if (draw.e2 < draw.dx)
		{
			draw.err += draw.dx;
			p0.iso_y += draw.sy;
		}
	}
}
