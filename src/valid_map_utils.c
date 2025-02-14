/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:32:03 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 16:47:54 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0)
		return (1);
	return (0);
}

int	is_color(char *line)
{
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		return (1);
	return (0);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	is_within_bounds(int x, int y, t_cub3d *cub)
{
	if (x >= 0 && x < cub->map_width
		&& y >= 0 && y < cub->map_height)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	z;

	z = 0;
	while ((s1[z] != '\0' || s2[z] != '\0') && n--)
	{
		if (s1[z] != s2[z])
			return ((unsigned char)s1[z] - (unsigned char)s2[z]);
		z++;
	}
	return (0);
}
