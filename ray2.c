/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:15:51 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 23:25:19 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
/*

void	calculate_ray_direction(t_cub3d *cub, int x, double *ray_dir_x,
		double *ray_dir_y)
{
	double	camera_x;

	camera_x = -(2 * x / (double)WINDOW_WIDTH - 1);
	*ray_dir_x = cub->dir_x - cub->plane_x * camera_x;
	*ray_dir_y = cub->dir_y - cub->plane_y * camera_x;
}

void	perform_dda(t_cub3d *cub, int *map_x, int *map_y, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			*map_x += cub->step_x;
			*side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			*map_y += cub->step_y;
			*side = 1;
		}
		if (*map_x < 0 || *map_x >= cub->map_width
			|| *map_y < 0 || *map_y >= cub->map_height)
			hit = 1;
		if (cub->map[*map_x][*map_y] == '1')
			hit = 1;
	}
}

void	raycasting(t_cub3d *cub)
{
	int		x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		side;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		calculate_ray_direction(cub, x, &ray_dir_x, &ray_dir_y);
		map_x = (int)cub->player_x;
		map_y = (int)cub->player_y;
		perform_dda(cub, &map_x, &map_y, &side);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}
*/