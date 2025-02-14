/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:15:51 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 14:16:06 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_cub3d *cub) {
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

void load_textures(t_cub3d *cub) {
    cub->north_texture.img = mlx_xpm_file_to_image(cub->mlx, cub->north_texture_path, &cub->north_texture.width, &cub->north_texture.height);
    cub->south_texture.img = mlx_xpm_file_to_image(cub->mlx, cub->south_texture_path, &cub->south_texture.width, &cub->south_texture.height);
    cub->west_texture.img = mlx_xpm_file_to_image(cub->mlx, cub->west_texture_path, &cub->west_texture.width, &cub->west_texture.height);
    cub->east_texture.img = mlx_xpm_file_to_image(cub->mlx, cub->east_texture_path, &cub->east_texture.width, &cub->east_texture.height);

    if (!cub->north_texture.img || !cub->south_texture.img || !cub->west_texture.img || !cub->east_texture.img) {
        fprintf(stderr, "Error: Failed to load textures.\n");
        exit(EXIT_FAILURE);
    }

    cub->north_texture.addr = mlx_get_data_addr(cub->north_texture.img, &cub->north_texture.bits_per_pixel, &cub->north_texture.line_length, &cub->north_texture.endian);
    cub->south_texture.addr = mlx_get_data_addr(cub->south_texture.img, &cub->south_texture.bits_per_pixel, &cub->south_texture.line_length, &cub->south_texture.endian);
    cub->west_texture.addr = mlx_get_data_addr(cub->west_texture.img, &cub->west_texture.bits_per_pixel, &cub->west_texture.line_length, &cub->west_texture.endian);
    cub->east_texture.addr = mlx_get_data_addr(cub->east_texture.img, &cub->east_texture.bits_per_pixel, &cub->east_texture.line_length, &cub->east_texture.endian);
}

void render_floor_ceiling(t_cub3d *cub)
{
    for (int y = 0; y < WINDOW_HEIGHT / 2; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            int pixel_index = y * cub->line_length + x * (cub->bits_per_pixel / 8);
            *(unsigned int *)(cub->addr + pixel_index) = cub->ceiling_color[0] << 16 | cub->ceiling_color[1] << 8 | cub->ceiling_color[2];
        }
    }

    for (int y = WINDOW_HEIGHT / 2; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            int pixel_index = y * cub->line_length + x * (cub->bits_per_pixel / 8);
            *(unsigned int *)(cub->addr + pixel_index) = cub->floor_color[0] << 16 | cub->floor_color[1] << 8 | cub->floor_color[2];
        }
    }
}
