/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:26 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/13 20:24:20 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TEXTURE_PATH 256
#define MAX_MAP_WIDTH 100
#define MAX_MAP_HEIGHT 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

typedef struct {
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_texture;

typedef struct {
    t_texture north_texture;
    t_texture south_texture;
    t_texture west_texture;
    t_texture east_texture;
    char *north_texture_path;
    char *south_texture_path;
    char *west_texture_path;
    char *east_texture_path;
    int floor_color[3];
    int ceiling_color[3];
    char map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
    int map_width;
    int map_height;
    char player_dir;
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    double player_x;
    double player_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    int keys[65536];
    double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
} t_cub3d;

//parcing.c
void	validate_map(t_cub3d *cub);
void	parse_map_line(char *line, t_cub3d *cub, int *map_started);
void	parse_texture(char *line, t_cub3d *cub);
void	parse_cub_file(const char *filename, t_cub3d *cub);
void	parse_color(char *line, t_cub3d *cub);
void	exit_error(const char *message);
int     is_texture(char *line);
int     is_color(char *line);
int     max(int a, int b);
void    set_player_position(t_cub3d *cub, char dir, int row, int col);
int     is_walkable(char c);
int     is_border(int x, int y, t_cub3d *cub);
int     adjacent_to_space(int x, int y, t_cub3d *cub);

//cub3dutils.c
void	render_floor_ceiling(t_cub3d *cub);
void	load_textures(t_cub3d *cub);
void	perform_dda(t_cub3d *cub, int *map_x, int *map_y, int *side);
void	calculate_ray_direction(t_cub3d *cub, int x, double *ray_dir_x,
    double *ray_dir_y);
void	init_player(t_cub3d *cub);
int	raycasting(t_cub3d *cub);




void parse_texture(char *line, t_cub3d *cub);
void parse_color(char *line, t_cub3d *cub);
void parse_map_line(char *line, t_cub3d *cub, int *map_started);
void validate_map(t_cub3d *cub);
void print_cub_data(t_cub3d *cub);
void free_resources(t_cub3d *cub);
void parse_cub_file(const char *filename, t_cub3d *cub);
void init_mlx(t_cub3d *cub);
void draw_map(t_cub3d *cub);
int close_window(t_cub3d *cub);
void init_player(t_cub3d *cub);
// int raycasting(t_cub3d *cub);
void load_textures(t_cub3d *cub);
void move_forward(t_cub3d *cub);
void move_backward(t_cub3d *cub);
void rotate_left(t_cub3d *cub);
void rotate_right(t_cub3d *cub);
//int key_press(int keycode, void *param);
void render_floor_ceiling(t_cub3d *cub);
int game_loop(t_cub3d *cub);
int key_press(int keycode, void *param);
int key_release(int keycode, void *param);
void move_right(t_cub3d *cub);
void move_left(t_cub3d *cub);
#endif


//gcc -Wall -Wextra -Werror -o cub3d cub3d.c parsing.c 3dUtils.c movements.c -L./minilibx -lmlx -lXext -lX11 -lm