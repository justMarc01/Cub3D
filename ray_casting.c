/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:15:24 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 14:31:12 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void calculate_line_height(double perp_dist, int *line_height)
{
	*line_height = (int)(WINDOW_HEIGHT / perp_dist);
}
static void calculate_draw_range(int line_height, int *draw_start, int *draw_end)
{
	*draw_start = -line_height/2 + WINDOW_HEIGHT/2;
	*draw_start = (*draw_start < 0) ? 0 : *draw_start;
	*draw_end = line_height/2 + WINDOW_HEIGHT/2;
	*draw_end = (*draw_end >= WINDOW_HEIGHT) ? WINDOW_HEIGHT-1 : *draw_end;
}
static void calculate_texture_x(t_cub3d *cub, int side, double *ray_dir,
							   double perp_dist, t_texture **tex, int *tex_x)
{
	double wall_x;
	if (side == 0)
		wall_x = cub->player_y + perp_dist * ray_dir[1];
	else
		wall_x = cub->player_x + perp_dist * ray_dir[0];
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)(*tex)->width);
	if ((side == 0 && ray_dir[0] > 0) || (side == 1 && ray_dir[1] < 0))
		*tex_x = (*tex)->width - *tex_x - 1;
}
static void get_wall_texture(t_cub3d *cub, int side, double *ray_dir, t_texture **tex)
{
	if (side == 0)
		*tex = (ray_dir[0] > 0) ? &cub->east_texture : &cub->west_texture;
	else
		*tex = (ray_dir[1] > 0) ? &cub->south_texture : &cub->north_texture;
}
static void draw_vertical_line(t_cub3d *cub, int x, t_texture *tex,
							  int tex_x, int draw_start, int draw_end)
{
	for (int y = draw_start; y < draw_end; y++) {
		const int relative_y = y - draw_start;
		const float percent = (float)relative_y / (draw_end - draw_start);
		int tex_y = (int)(percent * (tex->height - 1));
		tex_y = (tex_y < 0) ? 0 : (tex_y >= tex->height) ? tex->height-1 : tex_y;
		const int color = *(unsigned int*)(tex->addr +
			(tex_y * tex->line_length + tex_x * (tex->bits_per_pixel/8)));
		const int px_idx = y * cub->line_length + x * (cub->bits_per_pixel/8);
		*(unsigned int*)(cub->addr + px_idx) = color;
	}
}
int raycasting(t_cub3d *cub)
{
	render_floor_ceiling(cub);
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		double ray_dir[2];
		int map[2];
		double delta[2];
		int step[2];
		double side_dist[2];
		int side;
		double perp_dist;
		int line_height;
		int draw_start, draw_end;
		t_texture *tex;
		int tex_x;
		
		setup_ray(cub, x, ray_dir, map);
		calculate_deltas(ray_dir[0], ray_dir[1], delta);
		calculate_steps(cub, ray_dir[0], ray_dir[1], step, side_dist, delta);
		perform_dda(cub, map, step, side_dist, delta, &side);
		calculate_wall_dist(cub, side, map, step, ray_dir, &perp_dist);
		calculate_line_height(perp_dist, &line_height);
		calculate_draw_range(line_height, &draw_start, &draw_end);
		get_wall_texture(cub, side, ray_dir, &tex);
		calculate_texture_x(cub, side, ray_dir, perp_dist, &tex, &tex_x);
		draw_vertical_line(cub, x, tex, tex_x, draw_start, draw_end);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return 0;
}
