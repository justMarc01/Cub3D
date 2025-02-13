/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:15:51 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 19:38:58 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_cub3d *cub)
{
	cub->north_texture.img = mlx_xpm_file_to_image(cub->mlx,
			cub->north_texture_path, &cub->north_texture.width,
			&cub->north_texture.height);
	cub->south_texture.img = mlx_xpm_file_to_image(cub->mlx,
			cub->south_texture_path, &cub->south_texture.width,
			&cub->south_texture.height);
	cub->west_texture.img = mlx_xpm_file_to_image(cub->mlx,
			cub->west_texture_path, &cub->west_texture.width,
			&cub->west_texture.height);
	cub->east_texture.img = mlx_xpm_file_to_image(cub->mlx,
			cub->east_texture_path, &cub->east_texture.width,
			&cub->east_texture.height);
	if (!cub->north_texture.img || !cub->south_texture.img
		|| !cub->west_texture.img || !cub->east_texture.img)
		exit_error("Error: Failed to load textures.");
}
