/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 19:17:49 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map_line(char *line, t_cub3d *cub, int *map_started)
{
	static int	row;
	int			col;
	char		c;

	if (!*map_started)
		if (line[0] == '\0' || line[0] == '\n')
			return ;
	*map_started = 1;
	if (row >= MAX_MAP_HEIGHT)
		exit_error("Error: Map is too tall.");
	col = -1;
	while (line[++col] && line[col] != '\n')
	{
		if (col >= MAX_MAP_WIDTH)
			exit_error("Error: Map is too wide.");
		c = line[col];
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			set_player_position(cub, c, row, col);
		else if (c == '0' || c == '1' || c == ' ')
			cub->map[col][row] = c;
		else
			exit_error("Error: Invalid map character.");
	}
	row++, cub->map_height = row, cub->map_width = max(col, cub->map_width);
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
int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_border(int x, int y, t_cub3d *cub)
{
	return (x == 0 || x == cub->map_width - 1 || y == 0 || y == cub->map_height - 1);
}

int	adjacent_to_space(int x, int y, t_cub3d *cub)
{
	return (cub->map[x - 1][y] == ' ' || cub->map[x + 1][y] == ' ' ||
			cub->map[x][y - 1] == ' ' || cub->map[x][y + 1] == ' ');
}