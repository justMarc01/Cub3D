/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_catsing_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:20:52 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 14:29:54 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_ray(t_cub3d *cub, int x, double *ray_dir, int *map)
{
	const double	camera_x = -(2 * x / (double)WINDOW_WIDTH - 1);

	ray_dir[0] = cub->dir_x - cub->plane_x * camera_x;
	ray_dir[1] = cub->dir_y - cub->plane_y * camera_x;
	map[0] = (int)cub->player_x;
	map[1] = (int)cub->player_y;
}

void	calculate_deltas(double ray_dir_x, double ray_dir_y, double *delta)
{
	delta[0] = fabs(1 / ray_dir_x);
	delta[1] = fabs(1 / ray_dir_y);
}

void	calculate_steps(t_cub3d *cub, double ray_dir_x, double ray_dir_y,
						int *step, double *side_dist, double *delta)
{
	step[0] = (ray_dir_x < 0) ? -1 : 1;
	side_dist[0] = (ray_dir_x < 0) ?
		(cub->player_x - (int)cub->player_x) * delta[0] :
		((int)cub->player_x + 1.0 - cub->player_x) * delta[0];
	step[1] = (ray_dir_y < 0) ? -1 : 1;
	side_dist[1] = (ray_dir_y < 0) ?
		(cub->player_y - (int)cub->player_y) * delta[1] :
		((int)cub->player_y + 1.0 - cub->player_y) * delta[1];
}
void    perform_dda(t_cub3d *cub, int *map, int *step,
					   double *side_dist, double *delta, int *side)
{
	int hit = 0;
	while (!hit) {
		if (side_dist[0] < side_dist[1]) {
			side_dist[0] += delta[0];
			map[0] += step[0];
			*side = 0;
		} else {
			side_dist[1] += delta[1];
			map[1] += step[1];
			*side = 1;
		}
		if (map[0] < 0 || map[0] >= cub->map_width ||
			map[1] < 0 || map[1] >= cub->map_height) {
			hit = 1;
			break;
		}
		if (cub->map[map[0]][map[1]] == '1')
			hit = 1;
	}
}
void	calculate_wall_dist(t_cub3d *cub, int side, int *map, int *step,
							   double *ray_dir, double *perp_dist)
{
	if (side == 0) {
		*perp_dist = (map[0] - cub->player_x +
					 (1 - step[0])/2) / ray_dir[0];
	} else {
		*perp_dist = (map[1] - cub->player_y +
					 (1 - step[1])/2) / ray_dir[1];
	}
}
