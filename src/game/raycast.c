/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:10:33 by spike             #+#    #+#             */
/*   Updated: 2025/03/19 20:49:05 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void print_algo_data(t_data *algo)
{
    printf("=== DEBUG t_data ===\n");
    printf("Map Position: map_x = %d, map_y = %d\n", algo->map_x, algo->map_y);
    printf("Player Position: pos_x = %.6f, pos_y = %.6f\n", algo->pos_x, algo->pos_y);
    printf("Ray Direction: dir_x = %.6f, dir_y = %.6f\n", algo->dir_x, algo->dir_y);
    printf("Step: step_x = %d, step_y = %d\n", algo->step_x, algo->step_y);
    printf("Ray Distance: len_x = %.6f, len_y = %.6f\n", algo->len_x, algo->len_y);
    printf("Angle Increment: %.6f\n", algo->angle_increment);
    printf("=====================\n\n\n");
}
void	print_col_data(int drawStart, int drawEnd, double wall_pixel, int x, int half_screen, int half_wall)
{
	printf("=== DEBUG affichage ===\n");
	printf("   DrawStart = %d, DrawEnd = %d\n",drawStart, drawEnd);
	printf("   wall pixel = %f, half wall = %d, half screen = %d\n", wall_pixel, half_wall, half_screen);
	printf("   colonne = %d\n", x);

}




void print_colonne(t_game *game, int x, double wall_height, t_data *algo)
{
    int y;
    int wall_start;
    int wall_end;
    int color;

    // Déterminer les coordonnées de début et de fin du mur
    wall_start = (WINDOW_HEIGHT - wall_height) / 2;
    if (wall_start < 0)
        wall_start = 0;

    wall_end = (WINDOW_HEIGHT + wall_height) / 2;
    if (wall_end >= WINDOW_HEIGHT)
        wall_end = WINDOW_HEIGHT - 1;

    // Déterminer la couleur du mur en fonction de la direction du rayon
    if (algo->hit_side == 0) // Mur vertical (Est/Ouest)
        color = 0x00FF0000; // Rouge pour les murs Est/Ouest
    else // Mur horizontal (Nord/Sud)
        color = 0x000000FF; // Bleu pour les murs Nord/Sud

    // Dessiner le plafond (partie supérieure)
    y = 0;
    while (y < wall_start)
    {
        print_pixel(game, x, y, 0x00888888); // Gris pour le plafond
        y++;
    }

    // Dessiner le mur
    while (y < wall_end)
    {
        print_pixel(game, x, y, color);
        y++;
    }

    // Dessiner le sol (partie inférieure)
    while (y < WINDOW_HEIGHT)
    {
        print_pixel(game, x, y, 0x00444444); // Gris foncé pour le sol
        y++;
    }
}

double find_length(t_player *player, t_data *algo)
{
	double hypot;

	hypot = sqrt(pow(algo->pos_x - player->x, 2) + pow(algo->pos_y - player->y, 2));
	return (hypot * cos(player->rotation - atan2(algo->dir_y, algo->dir_x)));
}

void calculate_ray_length(t_data *algo)
{
	if (fabs(algo->dir_x) < 1e-6)
		algo->dir_x = 1e-6;

	if (fabs(algo->dir_y) < 1e-6)
		algo->dir_y = 1e-6;


	algo->delta_dist_x = fabs(1.0 / algo->dir_x);
	algo->delta_dist_y = fabs(1.0 / algo->dir_y);

	if (algo->step_x > 0)
		algo->len_x = (algo->map_x + 1.0 - algo->pos_x) * algo->delta_dist_x;
	else
		algo->len_x = (algo->pos_x - algo->map_x) * algo->delta_dist_x;


	if (algo->step_y > 0)
		algo->len_y = (algo->map_y + 1.0 - algo->pos_y) * algo->delta_dist_y;
	else
		algo->len_y = (algo->pos_y - algo->map_y) * algo->delta_dist_y;
}


void init_data(t_player *player, t_data *algo)
{
	algo->pos_x = player->x;
	algo->pos_y = player->y;
	algo->map_x = (int)algo->pos_x;
	algo->map_y = (int)algo->pos_y;

	if (algo->dir_x < 0)
		algo->step_x = -1;
	else
		algo->step_x = 1;

	if (algo->dir_y < 0)
		algo->step_y = -1;
	else
		algo->step_y = 1;

	calculate_ray_length(algo);
}

double dda_algo(t_player *player, t_data *algo, int **grid)
{
	init_data(player, algo);

	while (1)
	{
		if (algo->len_x < algo->len_y)
		{
			algo->hit_side = 0;
			algo->map_x += algo->step_x;
			algo->len_x += algo->delta_dist_x;
			if (algo->step_x > 0)
				algo->hit_direction = 2;
			else
				algo->hit_direction = 3; // 2 = Est, 3 = Ouest
		}
		else
		{
			algo->hit_side = 1;
			algo->map_y += algo->step_y;
			algo->len_y += algo->delta_dist_y;
			if (algo->step_x > 0)
				algo->hit_direction = 1;
			else
				algo->hit_direction = 0; // 1 = Sud, 0 = Nord
		}
		if (grid[algo->map_x][algo->map_y] == 1)
			break;

	}

	if (algo->hit_side == 0)
	{
		if (algo->step_x > 0)
			algo->pos_x = algo->map_x; // il tape a gauche
		else
			algo->pos_x = algo->map_x + 1; // il tape a droite

		algo->pos_y = player->y + (algo->pos_x - player->x) * algo->dir_y / algo->dir_x;
	}
	else
	{
		if (algo->step_y > 0)
			algo->pos_y = algo->map_y; // il tape en haut
		else
			algo->pos_y = algo->map_y + 1; // il tape en bas

		algo->pos_x = player->x + (algo->pos_y - player->y) * algo->dir_x / algo->dir_y;
	}

	return (find_length(player, algo));
}


void raycast(t_game *game, t_player *player, int **grid)
{
	t_data algo;
	double ray_angle;
	double length;
	double wall_height;
	int x = 0;
	double fov_rad = FOV * (PI / 180.0);

	algo.angle_increment = fov_rad / WINDOW_WIDTH;

	while (x < WINDOW_WIDTH)
	{
		algo.current_ray = x;
		ray_angle = player->rotation - (fov_rad / 2) + (x * algo.angle_increment);
		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);

		algo.dir_x = cos(ray_angle);
		algo.dir_y = sin(ray_angle);

		length = dda_algo(player, &algo, grid);
		wall_height = (WINDOW_HEIGHT / length);
		print_colonne(game, x, wall_height, &algo);
		x++;
	}
}
