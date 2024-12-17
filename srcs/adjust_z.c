#include "../include/fdf.h"

static void	adjust_total_gap(int i, int j, t_params *params, t_h_z *h_z)
{
	if (i > 0)
	{
		h_z->gap = abs(params->map[i][j].z - params->map[i - 1][j].z);
		if (h_z->gap != 0)
		{
			h_z->total_gap += h_z->gap;
			h_z->count++;
		}
	}
	if (j > 0)
	{
		h_z->gap = abs(params->map[i][j].z - params->map[i][j - 1].z);
		if (h_z->gap != 0)
		{
			h_z->total_gap += h_z->gap;
			h_z->count++;
		}
	}
}

static float	calculate_average_gap(t_params *params)
{
	int		i;
	int		j;
	t_h_z	h_z;

	h_z.total_gap = 0;
	h_z.count = 0;
	i = 0;
	while (i < params->map_info.map_height)
	{
		j = 0;
		while (j < params->map_info.map_width)
		{
			adjust_total_gap(i, j, params, &h_z);
			j++;
		}
		i++;
	}
	if (h_z.count == 0)
		return (0);
	return ((float)h_z.total_gap / h_z.count);
}

void	adjust_z_scale(t_params *params)
{
	float	average_gap;

	average_gap = calculate_average_gap(params);
	if (average_gap != 0)
		params->h_z = 1.0 / average_gap;
	else
		params->h_z = 1.0;
}
