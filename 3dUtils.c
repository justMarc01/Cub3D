/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3dUtils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:15:51 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/10 19:41:47 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_cub3d *cub) {
    cub->player_x = cub->player_x + 0.5; // Center the player in the tile
    cub->player_y = cub->player_y + 0.5; // Center the player in the tile

    if (cub->player_dir == 'N') {  // Facing North (up)
        cub->dir_x = 0;
        cub->dir_y = -1;
        cub->plane_x = 0.66;  // Left-right vision
        cub->plane_y = 0;
    } else if (cub->player_dir == 'S') {  // Facing South (down)
        cub->dir_x = 0;
        cub->dir_y = 1;
        cub->plane_x = -0.66;
        cub->plane_y = 0;
    } else if (cub->player_dir == 'E') {  // Facing East (right)
        cub->dir_x = 1;
        cub->dir_y = 0;
        cub->plane_x = 0;
        cub->plane_y = 0.66;
    } else if (cub->player_dir == 'W') {  // Facing West (left)
        cub->dir_x = -1;
        cub->dir_y = 0;
        cub->plane_x = 0;
        cub->plane_y = -0.66;
    }
}



int raycasting(t_cub3d *cub) {
    render_floor_ceiling(cub);
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        // Calculate ray position and direction
        double camera_x = -(2 * x / (double)WINDOW_WIDTH - 1); // X in camera space
        double ray_dir_x = cub->dir_x - cub->plane_x * camera_x;
        double ray_dir_y = cub->dir_y - cub->plane_y * camera_x;

        // Map position
        int map_x = (int)cub->player_x;
        int map_y = (int)cub->player_y;

        // Length of ray from one side to the next
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        // Step and initial side distance
        int step_x, step_y;
        double side_dist_x, side_dist_y;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (cub->player_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - cub->player_x) * delta_dist_x;
        }

        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (cub->player_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - cub->player_y) * delta_dist_y;
        }

        // Perform DDA (Digital Differential Analysis)
        int hit = 0;
        int side;
        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            // Check if current map position is out of bounds
            if (map_x < 0 || map_x >= cub->map_width || map_y < 0 || map_y >= cub->map_height) {
                hit = 1; // Treat as hitting a boundary (like a wall)
                break;
            }

            if (cub->map[map_x][map_y] == '1')
                hit = 1;
        }

        // Calculate distance to the wall
        double perp_wall_dist;
        if (side == 0) {
            perp_wall_dist = (map_x - cub->player_x + (1 - step_x) / 2) / ray_dir_x;
        } else {
            perp_wall_dist = (map_y - cub->player_y + (1 - step_y) / 2) / ray_dir_y;
        }

        // Calculate height of the line to draw on the screen
        int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);

        // Calculate lowest and highest pixel to fill in the current stripe
        int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;

        // Calculate texture coordinate
        double wall_x;
        if (side == 0) {
            wall_x = cub->player_y + perp_wall_dist * ray_dir_y;
        } else {
            wall_x = cub->player_x + perp_wall_dist * ray_dir_x;
        }
        wall_x -= floor(wall_x);

        // Choose texture based on wall side
        t_texture *texture;
        if (side == 0) {
            texture = (ray_dir_x > 0) ? &cub->east_texture : &cub->west_texture;
        } else {
            texture = (ray_dir_y > 0) ? &cub->south_texture : &cub->north_texture;
        }

        // Calculate texture X coordinate
        int tex_x = (int)(wall_x * (double)texture->width);
        if (side == 0 && ray_dir_x > 0) tex_x = texture->width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0) tex_x = texture->width - tex_x - 1;

        // Ensure texture coordinates are within bounds
        if (tex_x < 0 || tex_x >= texture->width) {
            fprintf(stderr, "Error: tex_x out of bounds (%d)\n", tex_x);
            exit(EXIT_FAILURE);
        }

        // Draw the textured wall
        for (int y = draw_start; y < draw_end; y++) {
            int relative_y = y - draw_start;
            float percent = (float)relative_y / (float)(draw_end - draw_start);
            int tex_y = (int)(percent * (texture->height - 1));

            if (tex_y < 0) tex_y = 0;
            else if (tex_y >= texture->height) tex_y = texture->height - 1;

            int color = *(unsigned int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
            int pixel_index = y * cub->line_length + x * (cub->bits_per_pixel / 8);
            *(unsigned int *)(cub->addr + pixel_index) = color;
        }
    }

    mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
    return 0;
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

void render_floor_ceiling(t_cub3d *cub) {
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