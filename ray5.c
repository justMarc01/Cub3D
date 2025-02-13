/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:15:51 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 23:26:10 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	render_floor_ceiling(t_cub3d *cub)
{
	int	x;
	int	y;
	int	pixel_index;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_index = y * cub->line_length
				+ x * (cub->bits_per_pixel / 8);
			*(unsigned int *)(cub->addr + pixel_index) = cub->ceiling_color[0]
				<< 16 | cub->ceiling_color[1] << 8 | cub->ceiling_color[2];
			x++;
		}
		y++;
	}
}
*/