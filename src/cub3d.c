/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:57:14 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 17:14:19 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit("Error: Failed to initialize minilibX.");
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->win)
		error_exit("Error: Failed to create window.");
	cub->img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->img)
		error_exit("Error: Failed to create image.");
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
}

void	draw_tile(t_cub3d *cub, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;
	int	pixel_index;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			pixel_x = x * TILE_SIZE + i;
			pixel_y = y * TILE_SIZE + j;
			if (pixel_x < WINDOW_WIDTH && pixel_y < WINDOW_HEIGHT)
			{
				pixel_index = pixel_y * cub->line_length
					+ pixel_x * (cub->bits_per_pixel / 8);
				*(unsigned int *)(cub->addr + pixel_index) = color;
			}
			j++;
		}
		i++;
	}
}

void	draw_map(t_cub3d *cub)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < cub->map_height)
	{
		x = 0;
		while (x < cub->map_width)
		{
			if (cub->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_tile(cub, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}

void	print_map(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->map_height)
	{
		x = 0;
		while (x < cub->map_width)
		{
			printf("%c", cub->map[x][y]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	game_loop(t_cub3d *cub)
{
	if (cub->keys[119])
		move_forward(cub);
	if (cub->keys[115])
		move_backward(cub);
	if (cub->keys[97])
		move_left(cub);
	if (cub->keys[100])
		move_right(cub);
	if (cub->keys[65361])
		rotate_left(cub);
	if (cub->keys[65363])
		rotate_right(cub);
	if (cub->keys[65307])
		close_window(cub);
	raycasting(cub);
	return (0);
}
