/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 19:18:19 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map(t_cub3d *cub)
{
	int	x, y;

	y = -1;
	while (++y < cub->map_height)
	{
		x = -1;
		while (++x < cub->map_width)
		{
			if (is_walkable(cub->map[x][y]))
			{
				if (is_border(x, y, cub))
					exit_error("Error: Map is not closed.");
				if (adjacent_to_space(x, y, cub))
					exit_error("Error: Map is not closed.");
			}
		}
	}
}
void	exit_error(const char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

int	is_texture(char *line)
{
	return (strncmp(line, "NO", 2) == 0 || strncmp(line, "SO", 2) == 0 ||
			strncmp(line, "WE", 2) == 0 || strncmp(line, "EA", 2) == 0);
}

int	is_color(char *line)
{
	return (strncmp(line, "F", 1) == 0 || strncmp(line, "C", 1) == 0);
}

int	max(int a, int b)
{
	return (a > b ? a : b);
}
