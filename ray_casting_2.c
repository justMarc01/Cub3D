/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:38:36 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 14:47:04 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_line_height(double perp_dist, int *line_height)
{
	*line_height = (int)(WINDOW_HEIGHT / perp_dist);
}

void	calculate_draw_range(int line_height, int *draw_start,
		int *draw_end)
{
	*draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT - 1;
}

void	calculate_texture_x(t_cub3d *cub, t_ray_info *ray_info, int *tex_x)
{
	double	wall_x;

	if (ray_info->side == 0)
		wall_x = cub->player_y + ray_info->perp_dist * ray_info->ray_dir[1];
	else
		wall_x = cub->player_x + ray_info->perp_dist * ray_info->ray_dir[0];
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)(*ray_info->tex)->width);
	if ((ray_info->side == 0 && ray_info->ray_dir[0] > 0)
		|| (ray_info->side == 1 && ray_info->ray_dir[1] < 0))
		*tex_x = (*ray_info->tex)->width - *tex_x - 1;
}
