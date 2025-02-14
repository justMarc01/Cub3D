/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:00:41 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 17:03:07 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_north_dir(double *dir_x, double *dir_y,
							double *plane_x, double *plane_y)
{
	*dir_x = 0;
	*dir_y = -1;
	*plane_x = 0.66;
	*plane_y = 0;
}

static void	set_south_dir(double *dir_x, double *dir_y,
							double *plane_x, double *plane_y)
{
	*dir_x = 0;
	*dir_y = 1;
	*plane_x = -0.66;
	*plane_y = 0;
}

static void	set_east_dir(double *dir_x, double *dir_y,
							double *plane_x, double *plane_y)
{
	*dir_x = 1;
	*dir_y = 0;
	*plane_x = 0;
	*plane_y = 0.66;
}

static void	set_west_dir(double *dir_x, double *dir_y,
							double *plane_x, double *plane_y)
{
	*dir_x = -1;
	*dir_y = 0;
	*plane_x = 0;
	*plane_y = -0.66;
}

void	init_player(t_cub3d *cub)
{
	cub->player_x += 0.5;
	cub->player_y += 0.5;
	if (cub->player_dir == 'N')
		set_north_dir(&cub->dir_x, &cub->dir_y, &cub->plane_x, &cub->plane_y);
	else if (cub->player_dir == 'S')
		set_south_dir(&cub->dir_x, &cub->dir_y, &cub->plane_x, &cub->plane_y);
	else if (cub->player_dir == 'E')
		set_east_dir(&cub->dir_x, &cub->dir_y, &cub->plane_x, &cub->plane_y);
	else if (cub->player_dir == 'W')
		set_west_dir(&cub->dir_x, &cub->dir_y, &cub->plane_x, &cub->plane_y);
}
