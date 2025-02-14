/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 18:38:12 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub_file(const char *filename, t_cub3d *cub)
{
	FILE	*file;
	char	line[MAX_LINE_LENGTH];
	int		map_started;

	file = fopen(filename, "r");
	if (!file)
		exit_error("Error opening file.");
	map_started = 0;
	while (fgets(line, MAX_LINE_LENGTH, file))
	{
		if (!map_started && is_texture(line))
			parse_texture(line, cub);
		else if (!map_started && is_color(line))
			parse_color(line, cub);
		else
			parse_map_line(line, cub, &map_started);
	}
	fclose(file);
	if (cub->player_dir == '\0')
		exit_error("Error: No player start position.");
	validate_map(cub);
}
