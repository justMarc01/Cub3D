/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:15:51 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 17:14:54 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_cub3d *cub, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		write(2, "Error: Failed to load texture.\n", 31);
		exit(EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

void	load_textures(t_cub3d *cub)
{
	load_texture(cub, &cub->north_texture, cub->north_texture_path);
	load_texture(cub, &cub->south_texture, cub->south_texture_path);
	load_texture(cub, &cub->west_texture, cub->west_texture_path);
	load_texture(cub, &cub->east_texture, cub->east_texture_path);
}

void	render_half_screen(t_cub3d *cub, int start, int end, int *color)
{
	int	y;
	int	x;
	int	pixel_index;
	int	color_value;

	y = start;
	while (y < end)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_index = y * cub->line_length + x * (cub->bits_per_pixel / 8);
			color_value = (color[0] << 16) | (color[1] << 8) | color[2];
			*(unsigned int *)(cub->addr + pixel_index) = color_value;
			x++;
		}
		y++;
	}
}

void	render_floor_ceiling(t_cub3d *cub)
{
	render_half_screen(cub, 0, WINDOW_HEIGHT / 2, cub->ceiling_color);
	render_half_screen(cub, WINDOW_HEIGHT / 2, WINDOW_HEIGHT, cub->floor_color);
}
