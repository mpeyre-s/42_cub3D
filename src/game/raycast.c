/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:54:11 by spike             #+#    #+#             */
/*   Updated: 2025/03/15 23:34:14 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// void print_column(t_game *game, int x, double wall_pixel)
// {
//     int drawStart;
// 	int drawEnd;
//     int y;

//     // Trouver le centre de l'écran
//     int half_screen = WINDOW_HEIGHT / 2;
//     int half_wall = wall_pixel / 2;

//     // Calcul des bornes du mur
//     drawStart = half_screen - half_wall;
//     drawEnd = half_screen + half_wall;

//     // Empêcher les dépassements de l'écran
//     if (drawStart < 0) drawStart = 0;
//     if (drawEnd > WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT;

//     // Affichage du ciel (de 0 à drawStart)
//     for (y = 0; y < drawStart; y++)
//     {
//         print_pixel(game, x, y, 0x87CEEB); // Bleu ciel
//     }

//     // Affichage du mur (de drawStart à drawEnd)
//     for (y = drawStart; y < drawEnd; y++)
//     {
//         print_pixel(game, x, y, 0x8B4513); // Marron (mur)
//     }

//     // Affichage du sol (de drawEnd à la fin de l'écran)
//     for (y = drawEnd; y < WINDOW_HEIGHT; y++)
//     {
//         print_pixel(game, x, y, 0x228B22); // Vert (sol)
//     }
// }

// double	move_while_no_wall(t_print *algo, t_player *player, int **grid)
// {
// 	double	perpWallDist;
// 	int		side;
// 	int		i = 0;

// 	//printf("itération dans la boucle %d\n", i);
// 	while (grid[algo->map_x][algo->map_y] == 0)
// 	{
// 		printf("itération dans la boucle %d\n", i);
// 		i++;
// 		if (algo->real_dist_x >= algo->real_dist_y)
// 		{
// 			algo->map_x += algo->steps_x;
// 			algo->real_dist_x += algo->abs_dist_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			algo->map_y += algo->steps_y;
// 			algo->real_dist_y += algo->abs_dist_y;
// 			side = 1;
// 		}
// 	}
// 	if (side == 0)
// 		perpWallDist = (algo->map_x - player->x + (1 - algo->steps_x) / 2) / algo->dir_x;
// 	else
// 		perpWallDist = (algo->map_y - player->y + (1 - algo->steps_y) / 2) / algo->dir_y;
// 	return (perpWallDist);

// }

// void	get_real_dist(t_print *algo, t_player *player)
// {
// 	if (algo->dir_x < 0)
// 	{
// 		algo->steps_x = -1;
// 		algo->real_dist_x = (player->x - algo->map_x) * algo->abs_dist_x;
// 	}
// 	else
// 	{
// 		algo->steps_x = 1;
// 		algo->real_dist_x = (algo->map_x + 1 - player->x) * algo->abs_dist_x;
// 	}
// 	if (algo->dir_y < 0)
// 	{
// 		algo->steps_y = -1;
// 		algo->real_dist_y = (player->y - algo->map_y) * algo->abs_dist_y;
// 	}
// 	else
// 	{
// 		algo->steps_y = 1;
// 		algo->real_dist_y = (algo->map_y + 1 - player->y) * algo->abs_dist_y;
// 	}
// }

// double	dda(t_player *player, int **grid, t_print *algo)
// {
// 	double	length;

// 	algo->map_x = (int)player->x;
// 	algo->map_y = (int)player->y;
// 	printf("map->x = %d, map->y = %d\n", algo->map_x, algo->map_y);

// 	if (algo->dir_x == 0)
// 		algo->dir_x = 1e-30;
// 	if (algo->dir_y == 0)
// 		algo->dir_y = 1e-30;

// 	algo->abs_dist_x = fabs(1 / algo->dir_x);
// 	algo->abs_dist_y = fabs(1 / algo->dir_y);

// 	get_real_dist(algo, player);
// 	length = move_while_no_wall(algo, player, grid);
// 	printf("Distance between the player and the wall = %f\n", length);
// 	return (length);
// }

// void	raycast(t_game *game, t_player *player, int **grid)
// {
// 	t_print	algo;
// 	double	ray_angle;
// 	double	length;
// 	double	wall_height;
// 	int		x;
// 	double	fov_rad = FOV * (PI / 180.0);

// 	algo.angle_increment = fov_rad / WINDOW_WIDTH;
// 	x = 0;

// 	while (x < WINDOW_WIDTH)
// 	{
// 		//ray_angle = player->rotation - (FOV / 2) + (x * algo.angle_increment);
// 		ray_angle = player->rotation - (fov_rad / 2) + (x * algo.angle_increment);

// 		//printf("player->rotation = %f\n", player->rotation);
// 		//printf("x = %d, x * angle increment = %f\n", x, x*algo.angle_increment);
// 		//printf("ray angle = %f\n", ray_angle);
// 		printf("position du joueur (%f, %f)\n", player->x, player->y);
// 		algo.dir_x = cos(ray_angle);
// 		algo.dir_y = sin(ray_angle);
// 		length = dda(player, grid, &algo);
// 		algo.correct_distance = length * fabs(cos(ray_angle - player->rotation));
// 		if (algo.correct_distance < 0.1)
// 			algo.correct_distance = 0.1;
// 		printf("length =  %f  correct distance = %f\n", length, algo.correct_distance);
// 		//double DIST_FACTOR = 0.75;
// 		wall_height = WINDOW_HEIGHT / algo.correct_distance;

// 		//wall_height = (1 / algo.correct_distance) * length;
// 		//wall_height = (1 / algo.correct_distance) * WINDOW_HEIGHT;
// 		//wall_height = (WINDOW_HEIGHT / algo.correct_distance) * WINDOW_WIDTH;
// 		//wall_height = fmin((1 / algo.correct_distance) * WINDOW_HEIGHT, WINDOW_HEIGHT);
// 		printf("(1 / algo.correct_distance) = %f // wall size = %f\n", 1/algo.correct_distance, wall_height);
// 		print_column(game, x, wall_height);
// 		x++;
// 	}
// }


void print_algo_data(t_data *algo)
{
    printf("=== DEBUG t_data ===\n");
    printf("Map Position: map_x = %d, map_y = %d\n", algo->map_x, algo->map_y);
    printf("Player Position: pos_x = %.6f, pos_y = %.6f\n", algo->pos_x, algo->pos_y);
    printf("Ray Direction: dir_x = %.6f, dir_y = %.6f\n", algo->dir_x, algo->dir_y);
    printf("Step: step_x = %d, step_y = %d\n", algo->step_x, algo->step_y);
    printf("Ray Distance: len_x = %.6f, len_y = %.6f\n", algo->len_x, algo->len_y);
    printf("Angle Increment: %.6f\n", algo->angle_increment);
    printf("=====================\n");
}


void print_column(t_game *game, int x, double wall_pixel)
{
    int drawStart;
	int drawEnd;
    int y;

	//printf("hello wtf ?\n");
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
// 	double distance;
// 	if (algo->len_x < algo->len_y)
// 	distance = (algo->map_x - player->x + (1 - algo->step_x) / 2) / algo->dir_x;
// else
// 	distance = (algo->map_y - player->y + (1 - algo->step_y) / 2) / algo->dir_y;

// return distance;
}


// // Fonction pour calculer la distance perpendiculaire (évite l'effet fish-eye)
// double find_length(t_player *player, t_data *algo)
// {
//     // Calculer la distance perpendiculaire (méthode sans effet fish-eye)
//     // Cette fonction n'est pas implémentée dans votre code, voici une suggestion
//     double dist;

//     if (algo->len_x < algo->len_y)
//         dist = (algo->map_x - player->x + (1 - algo->step_x) / 2) / algo->dir_x;
//     else
//         dist = (algo->map_y - player->y + (1 - algo->step_y) / 2) / algo->dir_y;

//     return fabs(dist); // Assurer que la distance est positive
// }















// Cette fonction calcule les longueurs jusqu'aux prochaines intersections
void calculate_ray_length(t_data *algo)
{
	// Éviter division par zéro
	if (fabs(algo->dir_x) < 1e-6)
		algo->dir_x = 1e-6;
	if (fabs(algo->dir_y) < 1e-6)
		algo->dir_y = 1e-6;

	// Calcul des longueurs
	if (algo->dir_x > 0)
		algo->len_x = ((algo->map_x + 1) - algo->pos_x) / algo->dir_x;
	else
	{
		algo->len_x = (algo->pos_x - algo->map_x) / (-algo->dir_x);
		if (algo->len_x < 1e-6) // Si on est exactement sur une ligne verticale
			algo->len_x = 1 / fabs(algo->dir_x);
	}

	if (algo->dir_y > 0)
		algo->len_y = ((algo->map_y + 1) - algo->pos_y) / algo->dir_y;
	else
	{
		algo->len_y = (algo->pos_y - algo->map_y) / (-algo->dir_y);
		if (algo->len_y < 1e-6) // Si on est exactement sur une ligne horizontale
			algo->len_y = 1 / fabs(algo->dir_y);
	}
}

// Cette fonction initialise les données pour le raycasting
void init_data(t_player *player, t_data *algo)
{
	algo->pos_x = player->x;
	algo->pos_y = player->y;
	algo->map_x = (int)algo->pos_x;
	algo->map_y = (int)algo->pos_y;

	// Initialisation des steps
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

	// Calcul initial des longueurs
	calculate_ray_length(algo);
}

double dda_algo(t_player *player, t_data *algo, int **grid)
{
	init_data(player, algo);

	while (1)
	{
		print_algo_data(algo); // Debug à chaque itération

		if (algo->len_x < algo->len_y)
		{
			// Avancer jusqu'à l'intersection verticale
			algo->pos_x += algo->len_x * algo->dir_x;
			algo->pos_y += algo->len_x * algo->dir_y;
			algo->map_x += algo->step_x;

			// Mettre à jour les longueurs
			algo->len_y -= algo->len_x;
			algo->len_x = 1.0 / fabs(algo->dir_x); // Distance pour traverser une case en X
		}
		else
		{
			// Avancer jusqu'à l'intersection horizontale
			algo->pos_x += algo->len_y * algo->dir_x;
			algo->pos_y += algo->len_y * algo->dir_y;
			algo->map_y += algo->step_y;

			// Mettre à jour les longueurs
			algo->len_x -= algo->len_y;
			algo->len_y = 1.0 / fabs(algo->dir_y); // Distance pour traverser une case en Y
		}

		// Vérifier si on a atteint un mur
		if (grid[algo->map_x][algo->map_y] == 1)
			break;
	}
	return find_length(player, algo);
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
		printf("x = %d?\n", x);
	}
}
