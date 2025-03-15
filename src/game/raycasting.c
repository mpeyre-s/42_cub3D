/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:10:33 by spike             #+#    #+#             */
/*   Updated: 2025/03/15 19:59:45 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void print_column(t_game *game, int x, double wall_pixel)
{
    int drawStart;
	int drawEnd;
    int y;

    // Trouver le centre de l'écran
    int half_screen = WINDOW_HEIGHT / 2;
    int half_wall = wall_pixel / 2;

    // Calcul des bornes du mur
    drawStart = half_screen - half_wall;
    drawEnd = half_screen + half_wall;

    // Empêcher les dépassements de l'écran
    if (drawStart < 0) drawStart = 0;
    if (drawEnd > WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT;

    // Affichage du ciel (de 0 à drawStart)
    for (y = 0; y < drawStart; y++)
    {
        print_pixel(game, x, y, 0x87CEEB); // Bleu ciel
    }

    // Affichage du mur (de drawStart à drawEnd)
    for (y = drawStart; y < drawEnd; y++)
    {
        print_pixel(game, x, y, 0x8B4513); // Marron (mur)
    }

    // Affichage du sol (de drawEnd à la fin de l'écran)
    for (y = drawEnd; y < WINDOW_HEIGHT; y++)
    {
        print_pixel(game, x, y, 0x228B22); // Vert (sol)
    }
}

double find_length(t_player *player, t_data *algo)
{
	double	hypot;
	double	theta;

	hypot = sqrt(pow(algo->pos_x - player->x, 2) + pow(algo->pos_y - player->y, 2));
	theta = atan2(algo->dir_y, algo->dir_x) - atan2(player->dir_y, player->dir_x);

	return (hypot * cos(theta));
}


void smallest_hypoth(t_data *algo)
{
	if (algo->dir_x > 0)
		algo->len_x = fabs((1 + algo->map_x - algo->pos_x) / algo->dir_x);
	else if (algo->dir_x < 0)
		algo->len_x = fabs((algo->pos_x - algo->map_x) / algo->dir_x);
	else
		algo->len_x = INFINITY;

	if (algo->dir_y > 0)
		algo->len_y = fabs((1 + algo->map_y - algo->pos_y) / algo->dir_y);
	else if (algo->dir_y < 0)
		algo->len_y = fabs((algo->pos_y - algo->map_y) / algo->dir_y);
	else
		algo->len_y = INFINITY;
}

void	init_data(t_player *player, t_data *algo)
{
	algo->pos_x = player->x;
	algo->pos_y = player->y;
	algo->map_x = (int) algo->pos_x;
	algo->map_y = (int) algo->pos_y;


	if (algo->dir_x < 0)
		algo->step_x = -1;
	else if (algo->dir_x > 0)
		algo->step_x = 1;
	else
		algo->step_x = 0;

	if (algo->dir_y < 0)
		algo->step_y = -1;
	else if (algo->dir_y > 0)
		algo->step_y = 1;
	else
		algo->step_y = 0;

}

double	dda_algo(t_player *player, t_data *algo, int **grid)
{
	init_data(player, algo);

	while (1)
	{
		smallest_hypoth(algo);
		if (algo->len_x < algo->len_y)
		{
			algo->pos_x += algo->len_x * algo->dir_x;
			algo->pos_y += algo->len_x * algo->dir_y;
			algo->map_x += algo->step_x;
		}
		else
		{
			algo->pos_x += algo->len_y * algo->dir_x;
			algo->pos_y += algo->len_y * algo->dir_y;
			algo->map_y += algo->step_y;
		}
		if (grid[algo->map_x][algo->map_y] == 1)
			break ;
	}
	return (find_length(player, algo));
}

void	raycast(t_game *game, t_player *player, int **grid)
{
	t_data	algo;
	double	ray_angle;
	double	length;
	double	wall_height;
	int		x;
	double	fov_rad;

	fov_rad = FOV * (PI / 180.0);

	algo.angle_increment = fov_rad / WINDOW_WIDTH;
	x = 0;

	while (x < WINDOW_WIDTH)
	{
		ray_angle = player->rotation - (fov_rad / 2) + (x * algo.angle_increment);
		algo.dir_x = cos(ray_angle);
		algo.dir_y = sin(ray_angle);
		length = dda_algo(player, &algo, grid);
		wall_height = WINDOW_HEIGHT / length;
		print_column(game, x, wall_height);
		x++;
	}
}
