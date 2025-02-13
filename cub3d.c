/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:57:14 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 22:03:21 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		fprintf(stderr, "Error: Failed to initialize minilibX.\n");
		exit(EXIT_FAILURE);
	}
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->win)
	{
		fprintf(stderr, "Error: Failed to create window.\n");
		exit(EXIT_FAILURE);
	}
	cub->img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->img)
	{
		fprintf(stderr, "Error: Failed to create image.\n");
		exit(EXIT_FAILURE);
	}
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel, &cub->line_length, &cub->endian);
}

void	draw_map(t_cub3d *cub)
{
	int tile_size = 20;
	int wall_color = 0xFFFFFF;
	int floor_color = 0x000000;
	
	for (int y = 0; y < cub->map_height; y++) {
		for (int x = 0; x < cub->map_width; x++) {
			int color = (cub->map[y][x] == '1') ? wall_color : floor_color;
			for (int i = 0; i < tile_size; i++) {
				for (int j = 0; j < tile_size; j++) {
					int pixel_x = x * tile_size + i;
					int pixel_y = y * tile_size + j;
					if (pixel_x < WINDOW_WIDTH && pixel_y < WINDOW_HEIGHT) {
						int pixel_index = pixel_y * cub->line_length + pixel_x * (cub->bits_per_pixel / 8);
						*(unsigned int *)(cub->addr + pixel_index) = color;
					}
				}
			}
		}
	}

	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}

int	close_window(t_cub3d *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(EXIT_SUCCESS);
}

void	print_map(t_cub3d *cub)
{
	for (int y = 0; y < cub->map_height; y++)
	{
		for (int x = 0; x < cub->map_width; x++)
		{
			printf("%c", cub->map[x][y]);
		}
		printf("\n");
	}
}

int	game_loop(t_cub3d *cub) {
	if (cub->keys[119]) move_forward(cub);
	if (cub->keys[115]) move_backward(cub);
	if (cub->keys[97]) move_left(cub);
	if (cub->keys[100]) move_right(cub);
	if (cub->keys[65361]) rotate_left(cub);
	if (cub->keys[65363]) rotate_right(cub);
	if (cub->keys[65307]) close_window(cub);

	raycasting(cub);
	return 0;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	t_cub3d cub = {0};
	parse_cub_file(argv[1], &cub);
	init_player(&cub);
	init_mlx(&cub);
	load_textures(&cub);
	mlx_hook(cub.win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub);
	mlx_hook(cub.win, 17, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return 0;
}
