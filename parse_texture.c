/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 18:11:48 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_strcpy(char *dst, const char *src);
static void	assign_texture_path(char *line, t_cub3d *cub, char *dup_path);

void	parse_texture(char *line, t_cub3d *cub)
{
	char	*path;
	char	*dup_path;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i])
		exit_error("Error: Invalid texture format.");
	path = line + i + 1;
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	dup_path = malloc(ft_strlen(path) + 1);
	if (!dup_path)
		exit_error("Error: Memory allocation failed.");
	ft_strcpy(dup_path, path);
	assign_texture_path(line, cub, dup_path);
}

static void	assign_texture_path(char *line, t_cub3d *cub, char *dup_path)
{
	if (!ft_strncmp(line, "NO", 2))
		cub->north_texture_path = dup_path;
	else if (!ft_strncmp(line, "SO", 2))
		cub->south_texture_path = dup_path;
	else if (!ft_strncmp(line, "WE", 2))
		cub->west_texture_path = dup_path;
	else if (!ft_strncmp(line, "EA", 2))
		cub->east_texture_path = dup_path;
	else
		exit_error("Error: Invalid texture identifier.");
}

static void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
