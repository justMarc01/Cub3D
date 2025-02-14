/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:15:24 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 14:54:43 by oabdelka         ###   ########.fr       */
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

static void	draw_vertical_line(t_cub3d *cub, int x, t_texture *tex,
		int tex_x, int draw_start, int draw_end)
{
	int	y;
	int	tex_y;
	int	relative_y;
	float	percent;
	int	color;
	int	px_idx;

	y = draw_start;
	while (y < draw_end)
	{
		relative_y = y - draw_start;
		percent = (float)relative_y / (draw_end - draw_start);
		tex_y = (int)(percent * (tex->height - 1));
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = *(unsigned int *)(tex->addr
				+ (tex_y * tex->line_length
				+ tex_x * (tex->bits_per_pixel / 8)));
		px_idx = y * cub->line_length + x * (cub->bits_per_pixel / 8);
		*(unsigned int *)(cub->addr + px_idx) = color;
		y++;
	}
}

static void	process_raycasting(t_cub3d *cub, int x)
{
	double		ray_dir[2];
	int			map[2];
	double		delta[2];
	int			step[2];
	double		side_dist[2];
	int			side;
	double		perp_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_texture	*tex;
	int			tex_x;
	t_ray_info	ray_info;

	setup_ray(cub, x, ray_dir, map);
	calculate_deltas(ray_dir[0], ray_dir[1], delta);
	calculate_steps(cub, ray_dir[0], ray_dir[1], step, side_dist, delta);
	perform_dda(cub, map, step, side_dist, delta, &side);
	calculate_wall_dist(cub, side, map, step, ray_dir, &perp_dist);
	calculate_line_height(perp_dist, &line_height);
	calculate_draw_range(line_height, &draw_start, &draw_end);
	get_wall_texture(cub, side, ray_dir, &tex);

	/* Initialize ray_info struct */
	ray_info.perp_dist = perp_dist;
	ray_info.side = side;
	ray_info.ray_dir = ray_dir;
	ray_info.tex = &tex;

	/* Pass struct instead of separate arguments */
	calculate_texture_x(cub, &ray_info, &tex_x);

	draw_vertical_line(cub, x, tex, tex_x, draw_start, draw_end);
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
