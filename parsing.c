/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:23 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/10 23:25:51 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parse texture lines (NO, SO, WE, EA)
void parse_texture(char *line, t_cub3d *cub) {
    char *path = strchr(line, ' ') + 1;
    path[strcspn(path, "\n")] = '\0'; // Remove newline

    if (strncmp(line, "NO", 2) == 0) {
        cub->north_texture_path = strdup(path);
    } else if (strncmp(line, "SO", 2) == 0) {
        cub->south_texture_path = strdup(path);
    } else if (strncmp(line, "WE", 2) == 0) {
        cub->west_texture_path = strdup(path);
    } else if (strncmp(line, "EA", 2) == 0) {
        cub->east_texture_path = strdup(path);
    } else {
        fprintf(stderr, "Error: Invalid texture identifier.\n");
        exit(EXIT_FAILURE);
    }
}

// Parse color lines (F, C)
void parse_color(char *line, t_cub3d *cub) {
    char *colors = strchr(line, ' ') + 1;
    colors[strcspn(colors, "\n")] = '\0'; // Remove newline

    int r, g, b;
    if (sscanf(colors, "%d,%d,%d", &r, &g, &b) != 3 || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: Invalid color format.\n");
        exit(EXIT_FAILURE);
    }

    if (strncmp(line, "F", 1) == 0) {
        cub->floor_color[0] = r;
        cub->floor_color[1] = g;
        cub->floor_color[2] = b;
    } else if (strncmp(line, "C", 1) == 0) {
        cub->ceiling_color[0] = r;
        cub->ceiling_color[1] = g;
        cub->ceiling_color[2] = b;
    } else {
        fprintf(stderr, "Error: Invalid color identifier.\n");
        exit(EXIT_FAILURE);
    }
}

// Parse map lines
void parse_map_line(char *line, t_cub3d *cub, int *map_started) {
    static int row = 0;

    if (!*map_started) {
        // Skip empty lines before the map starts
        if (line[0] == '\0' || line[0] == '\n') return;
        *map_started = 1;
    }

    if (row >= MAX_MAP_HEIGHT) {
        fprintf(stderr, "Error: Map is too tall.\n");
        exit(EXIT_FAILURE);
    }

    int col = 0;
    while (line[col] != '\0' && line[col] != '\n') {
        if (col >= MAX_MAP_WIDTH) {
            fprintf(stderr, "Error: Map is too wide.\n");
            exit(EXIT_FAILURE);
        }

        char c = line[col];
        if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
            if (cub->player_dir != '\0') {
                fprintf(stderr, "Error: Multiple player start positions.\n");
                exit(EXIT_FAILURE);
            }
            cub->player_dir = c;
            cub->player_x = col;  // Swap row and col here
            cub->player_y = row;  // Swap row and col here
            cub->map[col][row] = '0';  // Swap row and col here
        } else if (c == '0' || c == '1' || c == ' ') {
            cub->map[col][row] = c;  // Swap row and col here
        } else {
            fprintf(stderr, "Error: Invalid map character '%c'.\n", c);
            exit(EXIT_FAILURE);
        }
        col++;
    }

    cub->map_width = (col > cub->map_width) ? col : cub->map_width;
    row++;
    cub->map_height = row;
}

// Validate the map (check if it's closed/surrounded by walls)
void validate_map(t_cub3d *cub) {
    for (int y = 0; y < cub->map_height; y++) {
        for (int x = 0; x < cub->map_width; x++) {
            if (cub->map[x][y] == '0' || cub->map[x][y] == 'N' || cub->map[x][y] == 'S' || cub->map[x][y] == 'E' || cub->map[x][y] == 'W') {
                // Check if the cell is on the border
                if (x == 0 || x == cub->map_width - 1 || y == 0 || y == cub->map_height - 1) {
                    fprintf(stderr, "Error: Map is not closed.\n");
                    exit(EXIT_FAILURE);
                }

                // Check adjacent cells
                if (cub->map[x - 1][y] == ' ' || cub->map[x + 1][y] == ' ' || cub->map[x][y - 1] == ' ' || cub->map[x][y + 1] == ' ') {
                    fprintf(stderr, "Error: Map is not closed.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

// Main parsing function
void parse_cub_file(const char *filename, t_cub3d *cub) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int map_started = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (!map_started && (strncmp(line, "NO", 2) == 0 || strncmp(line, "SO", 2) == 0 || strncmp(line, "WE", 2) == 0 || strncmp(line, "EA", 2) == 0)) {
            parse_texture(line, cub);
        } else if (!map_started && (strncmp(line, "F", 1) == 0 || strncmp(line, "C", 1) == 0)) {
            parse_color(line, cub);
        } else {
            parse_map_line(line, cub, &map_started);
        }
    }

    fclose(file);

    if (cub->player_dir == '\0') {
        fprintf(stderr, "Error: No player start position found.\n");
        exit(EXIT_FAILURE);
    }

    validate_map(cub);
}
