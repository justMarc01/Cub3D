/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 14:07:23 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_map_dimensions(int row, int col)
{
	if (row >= MAX_MAP_HEIGHT)
		exit_error("Error: Map is too tall.");
	if (col >= MAX_MAP_WIDTH)
		exit_error("Error: Map is too wide.");
}

void	parse_map_line(char *line, t_cub3d *cub, int *map_started)
{
	static int	row;
	int			col;
	char		c;

	if (!*map_started)
	{
		if (line[0] == '\0' || line[0] == '\n')
			return ;
	}
	*map_started = 1;
	col = -1;
	while (line[++col] && line[col] != '\n')
	{
		validate_map_dimensions(row, col);
		c = line[col];
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			set_player_position(cub, c, row, col);
		else if (c == '0' || c == '1' || c == ' ')
			cub->map[col][row] = c;
		else
			exit_error("Error: Invalid map character.");
	}
	row++;
	cub->map_height = row;
	cub->map_width = max(col, cub->map_width);
}

void	set_player_position(t_cub3d *cub, char dir, int row, int col)
{
	if (cub->player_dir != '\0')
		exit_error("Error: Multiple player start positions.");
	cub->player_dir = dir;
	cub->player_x = col;
	cub->player_y = row;
	cub->map[col][row] = '0';
}
