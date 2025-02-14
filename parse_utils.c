/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:07:11 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 14:07:31 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_border(int x, int y, t_cub3d *cub)
{
	return (x == 0 || x == cub->map_width - 1
		|| y == 0 || y == cub->map_height - 1);
}

int	adjacent_to_space(int x, int y, t_cub3d *cub)
{
	return (cub->map[x - 1][y] == ' ' || cub->map[x + 1][y] == ' '
		|| cub->map[x][y - 1] == ' ' || cub->map[x][y + 1] == ' ');
}
