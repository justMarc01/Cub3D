/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:15:51 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 20:05:28 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub3d *cub)
{
	cub->player_x = cub->player_x + 0.5;
	cub->player_y = cub->player_y + 0.5;
	if (cub->player_dir == 'N')
	{
		cub->dir_x = 0;
		cub->dir_y = -1;
		cub->plane_x = 0.66;
		cub->plane_y = 0;
	}
	else if (cub->player_dir == 'S')
	{
		cub->dir_x = 0;
		cub->dir_y = 1;
		cub->plane_x = -0.66;
		cub->plane_y = 0;
	}
	else if (cub->player_dir == 'E')
	{
		cub->dir_x = 1;
		cub->dir_y = 0;
		cub->plane_x = 0;
		cub->plane_y = 0.66;
	}
	else if (cub->player_dir == 'W')
	{
		cub->dir_x = -1;
		cub->dir_y = 0;
		cub->plane_x = 0;
		cub->plane_y = -0.66;
	}
}
