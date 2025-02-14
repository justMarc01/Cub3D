/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:14:10 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 16:45:27 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_wall_texture(t_cub3d *cub, int side, double *ray_dir,
		t_texture **tex)
{
	if (side == 0)
	{
		if (ray_dir[0] > 0)
			*tex = &cub->east_texture;
		else
			*tex = &cub->west_texture;
	}
	else
	{
		if (ray_dir[1] > 0)
			*tex = &cub->south_texture;
		else
			*tex = &cub->north_texture;
	}
}

static void	draw_vertical_line(t_cub3d *cub, int x, t_ray_data *data)
{
	int		y;
	int		tex_y;
	float	percent;
	int		color;
	int		px_idx;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		percent = (float)(y - data->draw_start)
			/ (data->draw_end - data->draw_start);
		tex_y = (int)(percent * (data->tex->height - 1));
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= data->tex->height)
			tex_y = data->tex->height - 1;
		color = *(unsigned int *)(data->tex->addr
				+ (tex_y * data->tex->line_length
					+ data->tex_x * (data->tex->bits_per_pixel / 8)));
		px_idx = y * cub->line_length + x * (cub->bits_per_pixel / 8);
		*(unsigned int *)(cub->addr + px_idx) = color;
		y++;
	}
}

void	init_ray_data(t_ray_data *data)
{
	ft_memset(data, 0, sizeof(t_ray_data));
}

static void	process_raycasting(t_cub3d *cub, int x)
{
	t_ray_data	data;

	init_ray_data(&data);
	setup_ray(cub, x, &data);
	calculate_deltas(&data);
	calculate_steps(cub, &data);
	perform_dda(cub, &data);
	calculate_wall_dist(cub, &data);
	calculate_line_height(data.perp_dist, &data.line_height);
	calculate_draw_range(data.line_height, &data.draw_start, &data.draw_end);
	get_wall_texture(cub, data.side, data.ray_dir, &data.tex);
	calculate_texture_x(cub, &data, &data.tex_x);
	draw_vertical_line(cub, x, &data);
}

int	raycasting(t_cub3d *cub)
{
	int	x;

	render_floor_ceiling(cub);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		process_raycasting(cub, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
