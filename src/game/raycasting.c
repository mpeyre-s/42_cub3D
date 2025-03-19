/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:10:33 by spike             #+#    #+#             */
/*   Updated: 2025/03/19 15:40:38 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
void print_column(t_game *game, int x, double wall_pixel)
{
    int drawStart;
    int drawEnd;
    int y;

    int half_screen = WINDOW_HEIGHT / 2;
    int half_wall = (int)(wall_pixel / 2);

    drawStart = half_screen - half_wall;
    drawEnd = half_screen + half_wall;

    if (drawStart < 0) drawStart = 0;
    if (drawEnd > WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT;

    for (y = 0; y < drawStart; y++)
        print_pixel(game, x, y, 0x87CEEB);
    for (y = drawStart; y < drawEnd; y++)
        print_pixel(game, x, y, 0x8B4513);
    for (y = drawEnd; y < WINDOW_HEIGHT; y++)
        print_pixel(game, x, y, 0x228B22);
}

double find_length(t_player *player, t_data *algo)
{
    double wall_dist = fmin(algo->len_x, algo->len_y);
    double correction_factor = fabs(player->dir_x * algo->dir_x + player->dir_y * algo->dir_y);

    if (correction_factor > 0.0)
        wall_dist *= correction_factor;

    return fabs(wall_dist);
}

void set_hypoth(t_data *algo)
{
    algo->len_x = (algo->dir_x != 0) ? fabs((algo->map_x + (algo->dir_x > 0 ? 1.0 : 0.0) - algo->pos_x) / algo->dir_x) : INFINITY;
    algo->len_y = (algo->dir_y != 0) ? fabs((algo->map_y + (algo->dir_y > 0 ? 1.0 : 0.0) - algo->pos_y) / algo->dir_y) : INFINITY;
}

void init_data(t_player *player, t_data *algo)
{
    algo->pos_x = player->x;
    algo->pos_y = player->y;
    algo->map_x = (int) algo->pos_x;
    algo->map_y = (int) algo->pos_y;

    algo->step_x = (algo->dir_x > 0) ? 1 : (algo->dir_x < 0 ? -1 : 0);
    algo->step_y = (algo->dir_y > 0) ? 1 : (algo->dir_y < 0 ? -1 : 0);

    algo->delta_dist_x = (algo->dir_x != 0) ? fabs(1.0 / algo->dir_x) : INFINITY;
    algo->delta_dist_y = (algo->dir_y != 0) ? fabs(1.0 / algo->dir_y) : INFINITY;
}

double dda_algo(t_player *player, t_data *algo, int **grid)
{
    init_data(player, algo);
    set_hypoth(algo);

    while (algo->map_x >= 0  && algo->map_y >= 0)
    {
        if (algo->len_x < algo->len_y)
        {
            algo->map_x += algo->step_x;
            algo->len_x += algo->delta_dist_x;
        }
        else
        {
            algo->map_y += algo->step_y;
            algo->len_y += algo->delta_dist_y;
        }
        if (grid[algo->map_x][algo->map_y] == 1)
            break;
    }
    return find_length(player, algo);
}

void raycast(t_game *game, t_player *player, int **grid)
{
    t_data algo;
    double ray_angle;
    double length;
    double wall_height;
    int x;
    double fov_rad = FOV * (M_PI / 180.0);

    algo.angle_increment = fov_rad / WINDOW_WIDTH;

    for (x = 0; x < WINDOW_WIDTH; x++)
    {
        ray_angle = player->rotation - (fov_rad / 2) + (x * algo.angle_increment);
        algo.dir_x = cos(ray_angle);
        algo.dir_y = sin(ray_angle);

        length = dda_algo(player, &algo, grid);

        wall_height = (length > 0) ? WINDOW_HEIGHT / length : WINDOW_HEIGHT;
        print_column(game, x, wall_height);
    }
}
