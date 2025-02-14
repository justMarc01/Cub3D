/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:27:25 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 17:27:39 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2, NULL);
		return (EXIT_FAILURE);
	}
	ft_memset(&cub, 0, sizeof(t_cub3d));
	parse_cub_file(argv[1], &cub);
	init_player(&cub);
	init_mlx(&cub);
	load_textures(&cub);
	mlx_hook(cub.win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub);
	mlx_hook(cub.win, 17, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}

int	close_window(t_cub3d *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(EXIT_SUCCESS);
	return (0);
}
