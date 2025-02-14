/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 17:06:32 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map(t_cub3d *cub)
{
	int	visited[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
	int	x;
	int	y;

	ft_memset(visited, 0, sizeof(visited));
	flood_fill((int)cub->player_x, (int)cub->player_y, cub, visited);
	y = 0;
	while (y < cub->map_height)
	{
		x = 0;
		while (x < cub->map_width)
		{
			if (is_walkable(cub->map[x][y]))
			{
				if (is_border(x, y, cub))
					exit_error("Error: Map is not closed.");
				if (adjacent_to_space(x, y, cub))
					exit_error("Error: Map is not closed.");
			}
			x++;
		}
		y++;
	}
}

void	flood_fill(int x, int y, t_cub3d *cub,
					int visited[MAX_MAP_HEIGHT][MAX_MAP_WIDTH])
{
	if (x < 0 || x >= cub->map_width || y < 0 || y >= cub->map_height)
		exit_error("Error: Map is not closed.");
	if (cub->map[x][y] == '1' || visited[y][x])
		return ;
	visited[y][x] = 1;
	flood_fill(x + 1, y, cub, visited);
	flood_fill(x - 1, y, cub, visited);
	flood_fill(x, y + 1, cub, visited);
	flood_fill(x, y - 1, cub, visited);
}

void	exit_error(const char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}
