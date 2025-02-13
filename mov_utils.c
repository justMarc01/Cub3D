/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:24:07 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/13 19:32:17 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	move_right(t_cub3d *cub)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = cub->player_x + cub->plane_x * move_speed;
	new_y = cub->player_y + cub->plane_y * move_speed;
	if (new_x >= 0 && new_x < cub->map_width && new_y >= 0
		&& new_y < cub->map_height)
	{
		if (cub->map[(int)new_x][(int)new_y] == '0')
		{
			cub->player_x = new_x;
			cub->player_y = new_y;
		}
	}
}

void	rotate_left(t_cub3d *cub)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.05;
	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(rot_speed)
		+ cub->dir_y * sin(rot_speed);
	cub->dir_y = -old_dir_x * sin(rot_speed)
		+ cub->dir_y * cos(rot_speed);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(rot_speed)
		+ cub->plane_y * sin(rot_speed);
	cub->plane_y = -old_plane_x * sin(rot_speed)
		+ cub->plane_y * cos(rot_speed);
}

void	rotate_right(t_cub3d *cub)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.05;
	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(-rot_speed)
		+ cub->dir_y * sin(-rot_speed);
	cub->dir_y = -old_dir_x * sin(-rot_speed)
		+ cub->dir_y * cos(-rot_speed);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(-rot_speed)
		+ cub->plane_y * sin(-rot_speed);
	cub->plane_y = -old_plane_x * sin(-rot_speed)
		+ cub->plane_y * cos(-rot_speed);
}

int	key_press(int keycode, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	cub->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	cub->keys[keycode] = 0;
	return (0);
}
