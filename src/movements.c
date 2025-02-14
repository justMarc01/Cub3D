/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:29:24 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 19:29:22 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *cub)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = cub->player_x + cub->dir_x * move_speed;
	new_y = cub->player_y + cub->dir_y * move_speed;
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

void	move_backward(t_cub3d *cub)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = cub->player_x - cub->dir_x * move_speed;
	new_y = cub->player_y - cub->dir_y * move_speed;
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

void	move_left(t_cub3d *cub)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = cub->player_x - cub->plane_x * move_speed;
	new_y = cub->player_y - cub->plane_y * move_speed;
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
