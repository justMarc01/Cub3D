/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 19:11:48 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(char *line, t_cub3d *cub)
{
	char	*path;

	path = strchr(line, ' ') + 1;
	path[strcspn(path, "\n")] = '\0';
	if (strncmp(line, "NO", 2) == 0)
		cub->north_texture_path = strdup(path);
	else if (strncmp(line, "SO", 2) == 0)
		cub->south_texture_path = strdup(path);
	else if (strncmp(line, "WE", 2) == 0)
		cub->west_texture_path = strdup(path);
	else if (strncmp(line, "EA", 2) == 0)
		cub->east_texture_path = strdup(path);
	else
	{
		fprintf(stderr, "Error: Invalid texture identifier.\n");
		exit(EXIT_FAILURE);
	}
}
