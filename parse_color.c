/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 19:10:11 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *line, t_cub3d *cub)
{
	char	*colors;
	int		r, g, b;

	colors = strchr(line, ' ') + 1;
	colors[strcspn(colors, "\n")] = '\0';
	if (sscanf(colors, "%d,%d,%d", &r, &g, &b) != 3 || r < 0 || r > 255
		|| g < 0 || g > 255 || b < 0 || b > 255)
	{
		fprintf(stderr, "Error: Invalid color format.\n");
		exit(EXIT_FAILURE);
	}
	if (strncmp(line, "F", 1) == 0)
		cub->floor_color[0] = r, cub->floor_color[1] = g, cub->floor_color[2] = b;
	else if (strncmp(line, "C", 1) == 0)
		cub->ceiling_color[0] = r, cub->ceiling_color[1] = g, cub->ceiling_color[2] = b;
	else
	{
		fprintf(stderr, "Error: Invalid color identifier.\n");
		exit(EXIT_FAILURE);
	}
}
