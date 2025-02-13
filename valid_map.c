/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 23:38:40 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void validate_map(t_cub3d *cub)
{
    int visited[MAX_MAP_HEIGHT][MAX_MAP_WIDTH] = {0}; // Initialize visited array

    // Start flood fill from the player's position
    flood_fill((int)cub->player_x, (int)cub->player_y, cub, visited);

    // Additional checks (optional)
    for (int y = 0; y < cub->map_height; y++)
    {
        for (int x = 0; x < cub->map_width; x++)
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

void flood_fill(int x, int y, t_cub3d *cub, int visited[MAX_MAP_HEIGHT][MAX_MAP_WIDTH])
{
    // Check if the current cell is out of bounds
    if (x < 0 || x >= cub->map_width || y < 0 || y >= cub->map_height)
        exit_error("Error: Map is not closed.");

    // Check if the current cell is a wall or already visited
    if (cub->map[x][y] == '1' || visited[y][x])
        return;

    // Mark the current cell as visited
    visited[y][x] = 1;

    // Recursively flood fill in all four directions
    flood_fill(x + 1, y, cub, visited); // Right
    flood_fill(x - 1, y, cub, visited); // Left
    flood_fill(x, y + 1, cub, visited); // Down
    flood_fill(x, y - 1, cub, visited); // Up
}

int is_within_bounds(int x, int y, t_cub3d *cub)
{
    return (x >= 0 && x < cub->map_width && y >= 0 && y < cub->map_height);
}