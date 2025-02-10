/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:29:24 by mkaterji          #+#    #+#             */
/*   Updated: 2025/02/10 18:12:45 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_forward(t_cub3d *cub) {
    double move_speed = 0.1;
    double new_x = cub->player_x + cub->dir_x * move_speed;
    double new_y = cub->player_y + cub->dir_y * move_speed;

    // Check if new_x and new_y are within map bounds
    if (new_x >= 0 && new_x < cub->map_width && new_y >= 0 && new_y < cub->map_height) {
        // Check collision using map[x][y]
        if (cub->map[(int)new_x][(int)new_y] == '0') {
            cub->player_x = new_x;
            cub->player_y = new_y;
        }
    }
}
void move_backward(t_cub3d *cub) {
    double move_speed = 0.1;
    double new_x = cub->player_x - cub->dir_x * move_speed;
    double new_y = cub->player_y - cub->dir_y * move_speed;

    // Check if new_x and new_y are within map bounds
    if (new_x >= 0 && new_x < cub->map_width && new_y >= 0 && new_y < cub->map_height) {
        if (cub->map[(int)new_x][(int)new_y] == '0') {
            cub->player_x = new_x;
            cub->player_y = new_y;
        }
    }
}

void move_left(t_cub3d *cub) {  // A Key (Strafe Left)
    double move_speed = 0.1;
    double new_x = cub->player_x - cub->plane_x * move_speed;
    double new_y = cub->player_y - cub->plane_y * move_speed;

    // Check if new_x and new_y are within map bounds
    if (new_x >= 0 && new_x < cub->map_width && new_y >= 0 && new_y < cub->map_height) {
        // Check collision using the new position (atomic check)
        if (cub->map[(int)new_x][(int)new_y] == '0') {
            cub->player_x = new_x;
            cub->player_y = new_y;
        }
    }
}

void move_right(t_cub3d *cub) {   // D Key (Strafe Right)
    double move_speed = 0.1;
    double new_x = cub->player_x + cub->plane_x * move_speed;
    double new_y = cub->player_y + cub->plane_y * move_speed;

    // Check if new_x and new_y are within map bounds
    if (new_x >= 0 && new_x < cub->map_width && new_y >= 0 && new_y < cub->map_height) {
        // Check collision using the new position (atomic check)
        if (cub->map[(int)new_x][(int)new_y] == '0') {
            cub->player_x = new_x;
            cub->player_y = new_y;
        }
    }
}
void rotate_left(t_cub3d *cub) {
    double rot_speed = 0.05;
    double old_dir_x = cub->dir_x;

    cub->dir_x = cub->dir_x * cos(rot_speed) + cub->dir_y * sin(rot_speed);
    cub->dir_y = -old_dir_x * sin(rot_speed) + cub->dir_y * cos(rot_speed);

    double old_plane_x = cub->plane_x;
    cub->plane_x = cub->plane_x * cos(rot_speed) + cub->plane_y * sin(rot_speed);
    cub->plane_y = -old_plane_x * sin(rot_speed) + cub->plane_y * cos(rot_speed);
}

void rotate_right(t_cub3d *cub) {
    double rot_speed = 0.05;
    double old_dir_x = cub->dir_x;

    cub->dir_x = cub->dir_x * cos(-rot_speed) + cub->dir_y * sin(-rot_speed);
    cub->dir_y = -old_dir_x * sin(-rot_speed) + cub->dir_y * cos(-rot_speed);

    double old_plane_x = cub->plane_x;
    cub->plane_x = cub->plane_x * cos(-rot_speed) + cub->plane_y * sin(-rot_speed);
    cub->plane_y = -old_plane_x * sin(-rot_speed) + cub->plane_y * cos(-rot_speed);
}


// int key_press(int keycode, void *param) {
//     t_cub3d *cub = param;
//     printf("%d \n", keycode);
//     if (keycode == 119) move_forward(cub);        // W key
//     if (keycode == 115) move_backward(cub);      // S key
//     if (keycode == 65361) rotate_left(cub);        // left arrow key
//     if (keycode == 65363) rotate_right(cub);       // right arrow key
//     if (keycode == 65307) close_window(cub);      // ESC key
//     if (keycode == 97) move_left(cub);       // A
//     if (keycode == 100) move_right(cub);      // D

//     // Re-render the scene after movement
//     raycasting(cub);
//     return 0;
// }
// In main.c:
int key_press(int keycode, void *param) {
    t_cub3d *cub = (t_cub3d *)param;
    cub->keys[keycode] = 1; // Mark key as pressed
    return 0;
}

int key_release(int keycode, void *param) {
    t_cub3d *cub = (t_cub3d *)param;
    cub->keys[keycode] = 0; // Mark key as released
    return 0;
}

// int handle_input(t_cub3d *cub) {
//     if (cub->keys[119]) move_forward(cub);
//     if (cub->keys[115]) move_backward(cub);
//     if (cub->keys[97]) move_left(cub);
//     if (cub->keys[100]) move_right(cub);
//     if (cub->keys[65361]) rotate_left(cub);
//     if (cub->keys[65363]) rotate_right(cub);
//     if (cub->keys[65307]) close_window(cub);

//     raycasting(cub); // Re-render the scene after movement
//     return (0);
// }
