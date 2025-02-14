/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:24:26 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/14 19:08:45 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

// GNL
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strncpy_gnl(char *dest, const char *src, size_t n);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strdup_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);

/* ------------------------- */
/*        DEFINITIONS        */
/* ------------------------- */
# define MAX_LINE_LENGTH 1024
# define MAX_TEXTURE_PATH 256
# define MAX_MAP_WIDTH 100
# define MAX_MAP_HEIGHT 100
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define TILE_SIZE 20

/* ------------------------- */
/*       STRUCTURES          */
/* ------------------------- */

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_ray_data
{
	double		ray_dir[2];
	int			map[2];
	double		delta[2];
	int			step[2];
	double		side_dist[2];
	int			side;
	double		perp_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_texture	*tex;
	int			tex_x;
}	t_ray_data;

typedef struct s_ray_info
{
	double		perp_dist;
	int			side;
	double		*ray_dir;
	t_texture	**tex;
}	t_ray_info;

typedef struct s_cub3d
{
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	west_texture;
	t_texture	east_texture;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	int			floor_color[3];
	int			ceiling_color[3];
	char		map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
	int			map_width;
	int			map_height;
	char		player_dir;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			keys[65536];
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
}	t_cub3d;

/* ------------------------- */
/*      PARSING FUNCTIONS    */
/* ------------------------- */

void	validate_map(t_cub3d *cub);
void	parse_map_line(char *line, t_cub3d *cub, int *map_started);
void	parse_texture(char *line, t_cub3d *cub);
void	parse_cub_file(const char *filename, t_cub3d *cub);
void	parse_color(char *line, t_cub3d *cub);
void	exit_error(const char *message);
int		is_texture(char *line);
int		is_color(char *line);
int		max(int a, int b);
void	set_player_position(t_cub3d *cub, char dir, int row, int col);
int		is_walkable(char c);
int		is_border(int x, int y, t_cub3d *cub);
int		adjacent_to_space(int x, int y, t_cub3d *cub);
void	flood_fill(int x, int y, t_cub3d *cub,
			int visited[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]);
int		is_within_bounds(int x, int y, t_cub3d *cub);
int		extract_rgb(char *colors, int *rgb);

/* ------------------------- */
/*       GAME ENGINE         */
/* ------------------------- */

void	render_floor_ceiling(t_cub3d *cub);
void	load_textures(t_cub3d *cub);
void	init_player(t_cub3d *cub);
int		raycasting(t_cub3d *cub);
void	init_mlx(t_cub3d *cub);
void	error_exit(const char *message);
int		ft_strlen(const char *s);
void	ft_putstr_fd(const char *s, int fd, char *arg);
void	draw_map(t_cub3d *cub);
int		close_window(t_cub3d *cub);
void	free_resources(t_cub3d *cub);
int		game_loop(t_cub3d *cub);

/* ------------------------- */
/*      MOVEMENT & INPUT     */
/* ------------------------- */

void	move_forward(t_cub3d *cub);
void	move_backward(t_cub3d *cub);
void	rotate_left(t_cub3d *cub);
void	rotate_right(t_cub3d *cub);
void	move_right(t_cub3d *cub);
void	move_left(t_cub3d *cub);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);

/* ------------------------- */
/*      RAY CASTING          */
/* ------------------------- */

void	init_ray_data(t_ray_data *data);
void	setup_ray(t_cub3d *cub, int x, t_ray_data *ray);
void	calculate_deltas(t_ray_data *ray);
void	calculate_steps(t_cub3d *cub, t_ray_data *ray);
void	perform_dda(t_cub3d *cub, t_ray_data *ray);
void	calculate_wall_dist(t_cub3d *cub, t_ray_data *ray);
void	calculate_line_height(double perp_dist, int *line_height);
void	calculate_draw_range(int line_height, int *draw_start, int *draw_end);
void	calculate_texture_x(t_cub3d *cub, t_ray_data *ray_data, int *tex_x);

/* ------------------------- */
/*        UTILITIES          */
/* ------------------------- */

void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif /* CUB3D_H */
