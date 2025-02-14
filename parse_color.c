/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:56:54 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 17:46:27 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_color_values(t_cub3d *cub, char id, int rgb[3]);
static int	skip_spaces(char *colors, int *i);
static int	parse_number(char *colors, int *i);

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
		ft_putstr_fd("Error: Invalid color identifier.\n", 2, NULL);
		exit(EXIT_FAILURE);
	}
}

void	parse_color(char *line, t_cub3d *cub)
{
	int		rgb[3];
	int		i;
	int		j;
	char	colors[20];

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	j = 0;
	while (line[i] && line[i] != '\n' && j < 19)
		colors[j++] = line[i++];
	colors[j] = '\0';
	if (!extract_rgb(colors, rgb))
	{
		ft_putstr_fd("Error: Invalid color format.\n", 2, NULL);
		exit(EXIT_FAILURE);
	}
	set_color_values(cub, line[0], rgb);
}

int	extract_rgb(char *colors, int *rgb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		if (!skip_spaces(colors, &i) || colors[i] < '0' || colors[i] > '9')
			return (0);
		rgb[j] = parse_number(colors, &i);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (0);
		if (++j < 3 && (skip_spaces(colors, &i) != ',' || colors[i++] != ','))
			return (0);
	}
	return (skip_spaces(colors, &i) == '\0');
}

static int	skip_spaces(char *colors, int *i)
{
	while (colors[*i] == ' ' || colors[*i] == '\t')
		(*i)++;
	return (colors[*i]);
}

static int	parse_number(char *colors, int *i)
{
	int	num;

	num = 0;
	while (colors[*i] >= '0' && colors[*i] <= '9')
	{
		num = num * 10 + (colors[*i] - '0');
		(*i)++;
	}
	return (num);
}
