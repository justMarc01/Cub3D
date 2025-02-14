/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:56:54 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 14:03:16 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_color_values(t_cub3d *cub, char id, int rgb[3]);

static void	set_color_values(t_cub3d *cub, char id, int rgb[3])
{
	if (id == 'F')
	{
		cub->floor_color[0] = rgb[0];
		cub->floor_color[1] = rgb[1];
		cub->floor_color[2] = rgb[2];
	}
	else if (id == 'C')
	{
		cub->ceiling_color[0] = rgb[0];
		cub->ceiling_color[1] = rgb[1];
		cub->ceiling_color[2] = rgb[2];
	}
	else
	{
		fprintf(stderr, "Error: Invalid color identifier.\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_color(char *line, t_cub3d *cub)
{
	char	*colors;
	int		rgb[3];

	colors = strchr(line, ' ') + 1;
	colors[strcspn(colors, "\n")] = '\0';
	if (sscanf(colors, "%d,%d,%d", &rgb[0], &rgb[1], &rgb[2]) != 3
		|| rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		fprintf(stderr, "Error: Invalid color format.\n");
		exit(EXIT_FAILURE);
	}
	set_color_values(cub, line[0], rgb);
}
