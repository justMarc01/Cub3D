/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_catsing_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:29:54 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 16:41:16 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_ray(t_cub3d *cub, int x, t_ray_data *ray)
{
	const double	camera_x = -(2 * x / (double)WINDOW_WIDTH - 1);

	ray->ray_dir[0] = cub->dir_x - cub->plane_x * camera_x;
	ray->ray_dir[1] = cub->dir_y - cub->plane_y * camera_x;
	ray->map[0] = (int)cub->player_x;
	ray->map[1] = (int)cub->player_y;
}

void	calculate_deltas(t_ray_data *ray)
{
	ray->delta[0] = fabs(1 / ray->ray_dir[0]);
	ray->delta[1] = fabs(1 / ray->ray_dir[1]);
}

void	calculate_steps(t_cub3d *cub, t_ray_data *ray)
{
	if (ray->ray_dir[0] < 0)
	{
		ray->step[0] = -1;
		ray->side_dist[0] = (cub->player_x - ray->map[0]) * ray->delta[0];
	}
	else
	{
		ray->step[0] = 1;
		ray->side_dist[0] = (ray->map[0] + 1.0 - cub->player_x) * ray->delta[0];
	}
	if (ray->ray_dir[1] < 0)
	{
		ray->step[1] = -1;
		ray->side_dist[1] = (cub->player_y - ray->map[1]) * ray->delta[1];
	}
	else
	{
		ray->step[1] = 1;
		ray->side_dist[1] = (ray->map[1] + 1.0 - cub->player_y) * ray->delta[1];
	}
}

void	perform_dda(t_cub3d *cub, t_ray_data *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist[0] < ray->side_dist[1])
		{
			ray->side_dist[0] += ray->delta[0];
			ray->map[0] += ray->step[0];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[1] += ray->delta[1];
			ray->map[1] += ray->step[1];
			ray->side = 1;
		}
		if (ray->map[0] < 0 || ray->map[0] >= cub->map_width
			|| ray->map[1] < 0 || ray->map[1] >= cub->map_height
			|| cub->map[ray->map[0]][ray->map[1]] == '1')
			hit = 1;
	}
}

void	calculate_wall_dist(t_cub3d *cub, t_ray_data *ray)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map[0] - cub->player_x + (1 - ray->step[0]) / 2)
			/ ray->ray_dir[0];
	else
		ray->perp_dist = (ray->map[1] - cub->player_y + (1 - ray->step[1]) / 2)
			/ ray->ray_dir[1];
}
