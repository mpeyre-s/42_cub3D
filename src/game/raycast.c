/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:10:33 by spike             #+#    #+#             */
/*   Updated: 2025/03/19 14:03:27 by spike            ###   ########.fr       */
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

	//print_col_data(drawStart, drawEnd, wall_pixel, x, half_screen, half_wall);
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



// double find_length(t_player *player, t_data *algo)
// {
// 	double hypot;
// 	double theta;
// 	hypot = sqrt(pow(algo->pos_x - player->x, 2) + pow(algo->pos_y - player->y, 2));
// 	theta = atan2(algo->dir_y, algo->dir_x) - atan2(player->dir_y, player->dir_x);
// 	return (hypot * cos(theta));
// }



// // void set_hypoth(t_data *algo)
// // {
// // 	if (algo->dir_x > 0)
// // 		algo->len_x = (algo->map_x + 1.0 - algo->pos_x) / algo->dir_x;
// //     else if (algo->dir_x < 0)
// //         algo->len_x = (algo->map_x - algo->pos_x) / algo->dir_x;
// //     else
// //         algo->len_x = INFINITY;

// //     if (algo->dir_y > 0)
// //         algo->len_y = (algo->map_y + 1.0 - algo->pos_y) / algo->dir_y;
// //     else if (algo->dir_y < 0)
// //         algo->len_y = (algo->map_y - algo->pos_y) / algo->dir_y;
// //     else
// //         algo->len_y = INFINITY;

// //     // Assurer que les distances sont positives (important!)
// //     algo->len_x = fabs(algo->len_x);
// //     algo->len_y = fabs(algo->len_y);
// // }

// // void	init_data(t_player *player, t_data *algo)
// // {
// // 	algo->pos_x = player->x;
// // 	algo->pos_y = player->y;
// // 	algo->map_x = (int) algo->pos_x;
// // 	algo->map_y = (int) algo->pos_y;


// // 	if (algo->dir_x < 0)
// // 		algo->step_x = -1;
// // 	else if (algo->dir_x > 0)
// // 		algo->step_x = 1;
// // 	else
// // 		algo->step_x = 0;

// // 	if (algo->dir_y < 0)
// // 		algo->step_y = -1;
// // 	else if (algo->dir_y > 0)
// // 		algo->step_y = 1;
// // 	else
// // 		algo->step_y = 0;

// // 	algo->delta_dist_x = (algo->dir_x != 0) ? fabs(1 / algo->dir_x) : INFINITY;
// // 	algo->delta_dist_y = (algo->dir_y != 0) ? fabs(1 / algo->dir_y) : INFINITY;

// // }

// // double	dda_algo(t_player *player, t_data *algo, int **grid)
// // {
// // 	init_data(player, algo);
// // 	set_hypoth(algo);

// // 	while (1)
// // 	{
// // 		print_algo_data(algo);
// // 		if (algo->len_x < algo->len_y)
// // 		{
// // 			// On avance dans la direction X
// // 			algo->map_x += algo->step_x;
// // 			algo->len_x += algo->delta_dist_x; // On avance vers la prochaine frontière verticale
// // 		}
// // 		else
// // 		{
// // 			// On avance dans la direction Y
// // 			algo->map_y += algo->step_y;
// // 			algo->len_y += algo->delta_dist_y; // On avance vers la prochaine frontière horizontale
// // 		}
// // 		if (grid[algo->map_x][algo->map_y] == 1)
// // 		{
// // 			printf("grid[%d][%d]\n\n", algo->map_x, algo->map_y);
// // 			break ;
// // 		}
// // 		printf("grid[%d][%d]\n\n", algo->map_x, algo->map_y);
// // 	}
// // 	return (find_length(player, algo));
// // }



















// void calculate_ray_length(t_data *algo)
// {
// 	// Éviter division par zéro
// 	if (fabs(algo->dir_x) < 1e-6)
// 		algo->dir_x = 1e-6;
// 	if (fabs(algo->dir_y) < 1e-6)
// 		algo->dir_y = 1e-6;

// 	// Calcul des longueurs
// 	if (algo->dir_x > 0)
// 		algo->len_x = ((algo->map_x + 1) - algo->pos_x) / algo->dir_x;
// 	else
// 	{
// 		algo->len_x = (algo->pos_x - algo->map_x) / (-algo->dir_x);
// 		if (algo->len_x < 1e-6) // Si on est exactement sur une ligne verticale
// 			algo->len_x = 1 / fabs(algo->dir_x);
// 	}
// 	if (algo->dir_y > 0)
// 		algo->len_y = ((algo->map_y + 1) - algo->pos_y) / algo->dir_y;
// 	else
// 	{
// 		algo->len_y = (algo->pos_y - algo->map_y) / (-algo->dir_y);
// 		if (algo->len_y < 1e-6) // Si on est exactement sur une ligne horizontale
// 			algo->len_y = 1 / fabs(algo->dir_y);
// 	}
// }

// // Cette fonction initialise les données pour le raycasting
// void init_data(t_player *player, t_data *algo)
// {
// 	algo->pos_x = player->x;
// 	algo->pos_y = player->y;
// 	algo->map_x = (int)algo->pos_x;
// 	algo->map_y = (int)algo->pos_y;

// 	// Initialisation des steps
// 	if (algo->dir_x < 0)
// 		algo->step_x = -1;
// 	else if (algo->dir_x > 0)
// 		algo->step_x = 1;
// 	else
// 		algo->step_x = 0;

// 	if (algo->dir_y < 0)
// 		algo->step_y = -1;
// 	else if (algo->dir_y > 0)
// 		algo->step_y = 1;
// 	else
// 		algo->step_y = 0;
// 	// Calcul initial des longueurs
// 	calculate_ray_length(algo);
// }


// double	dda_algo(t_player *player, t_data *algo, int **grid)
// {
// 	init_data(player, algo);
// 	while (1)
// 	{
// 		print_algo_data(algo); // Debug à chaque itération
// 		if (algo->len_x < algo->len_y)
// 		{
// 			// Avancer jusqu'à l'intersection verticale
// 			algo->pos_x += algo->len_x * algo->dir_x;
// 			algo->pos_y += algo->len_x * algo->dir_y;
// 			algo->map_x += algo->step_x;

// 			// Mettre à jour les longueurs
// 			algo->len_y -= algo->len_x;
// 			algo->len_x = 1.0 / fabs(algo->dir_x); // Distance pour traverser une case en X
// 		}
// 		else
// 		{
// 			// Avancer jusqu'à l'intersection horizontale
// 			algo->pos_x += algo->len_y * algo->dir_x;
// 			algo->pos_y += algo->len_y * algo->dir_y;
// 			algo->map_y += algo->step_y;

// 			// Mettre à jour les longueurs
// 			algo->len_x -= algo->len_y;
// 			algo->len_y = 1.0 / fabs(algo->dir_y); // Distance pour traverser une case en Y
// 		}

// 		// Vérifier si on a atteint un mur
// 		if (grid[algo->map_x][algo->map_y] == 1)
// 			break;
// 	}
// 	return find_length(player, algo);
// }

// void	raycast(t_game *game, t_player *player, int **grid)
// {
// 	t_data	algo;
// 	double	ray_angle;
// 	double	length;
// 	double	wall_height;
// 	int		x;
// 	double	fov_rad;

// 	fov_rad = FOV * (PI / 180.0);

// 	algo.angle_increment = fov_rad / WINDOW_WIDTH;
// 	x = 0;

// 	while (x < WINDOW_WIDTH)
// 	{
// 		algo.current_ray = x;
// 		ray_angle = player->rotation - (fov_rad / 2) + (x * algo.angle_increment);
// 		algo.dir_x = cos(ray_angle);
// 		algo.dir_y = sin(ray_angle);
// 		length = dda_algo(player, &algo, grid);
//        	wall_height = (WINDOW_HEIGHT / length);
// 		print_colonne(game, x, wall_height, &algo);
// 		x++;
// 		printf("pixel x = %d\nwall_height = %f\n", x, wall_height);
// 	}
// }



// // Calcule la distance du rayon jusqu'au mur
// double find_length(t_player *player, t_data *algo)
// {
//     // Calcul de la distance euclidienne
//     double dx = algo->pos_x - player->x;
//     double dy = algo->pos_y - player->y;
//     double distance = sqrt(dx * dx + dy * dy);

//     // Correction de l'effet fisheye
//     double player_angle = player->rotation;
//     double ray_angle = atan2(algo->dir_y, algo->dir_x);
//     double angle_diff = ray_angle - player_angle;

//     // Normaliser l'angle entre -PI et PI
//     while (angle_diff > PI)
//         angle_diff -= 2 * PI;
//     while (angle_diff < -PI)
//         angle_diff += 2 * PI;

//     // Correction de l'effet fisheye
//     distance *= cos(angle_diff);

//     return distance;
// }

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

double find_length(t_player *player, t_data *algo) {
    double hypot = sqrt(pow(algo->pos_x - player->x, 2) + pow(algo->pos_y - player->y, 2));
    return hypot * cos(player->rotation - atan2(algo->dir_y, algo->dir_x));
}

void calculate_ray_length(t_data *algo) {
    if (fabs(algo->dir_x) < 1e-6) {
        algo->dir_x = 1e-6;
    }
    if (fabs(algo->dir_y) < 1e-6) {
        algo->dir_y = 1e-6;
    }

    algo->delta_dist_x = fabs(1.0 / algo->dir_x);
    algo->delta_dist_y = fabs(1.0 / algo->dir_y);

    if (algo->step_x > 0) {
        algo->len_x = (algo->map_x + 1.0 - algo->pos_x) * algo->delta_dist_x;
    } else {
        algo->len_x = (algo->pos_x - algo->map_x) * algo->delta_dist_x;
    }

    if (algo->step_y > 0) {
        algo->len_y = (algo->map_y + 1.0 - algo->pos_y) * algo->delta_dist_y;
    } else {
        algo->len_y = (algo->pos_y - algo->map_y) * algo->delta_dist_y;
    }
}

void init_data(t_player *player, t_data *algo) {
    algo->pos_x = player->x;
    algo->pos_y = player->y;
    algo->map_x = (int)algo->pos_x;
    algo->map_y = (int)algo->pos_y;

    if (algo->dir_x < 0) {
        algo->step_x = -1;
    } else {
        algo->step_x = 1;
    }

    if (algo->dir_y < 0) {
        algo->step_y = -1;
    } else {
        algo->step_y = 1;
    }

    calculate_ray_length(algo);
}

double dda_algo(t_player *player, t_data *algo, int **grid) {
    init_data(player, algo);

    while (1) {
        if (algo->len_x < algo->len_y) {
            algo->hit_side = 0;
            algo->map_x += algo->step_x;
            algo->len_x += algo->delta_dist_x;
            algo->hit_direction = (algo->step_x > 0) ? 2 : 3; // 2 = Est, 3 = Ouest
        } else {
            algo->hit_side = 1;
            algo->map_y += algo->step_y;
            algo->len_y += algo->delta_dist_y;
            algo->hit_direction = (algo->step_y > 0) ? 1 : 0; // 1 = Sud, 0 = Nord
        }
        if (grid[algo->map_x][algo->map_y] == 1) {
            break;
        }
    }

    if (algo->hit_side == 0) {
        if (algo->step_x > 0) {
            algo->pos_x = algo->map_x;
        } else {
            algo->pos_x = algo->map_x + 1;
        }
        algo->pos_y = player->y + (algo->pos_x - player->x) * algo->dir_y / algo->dir_x;
    } else {
        if (algo->step_y > 0) {
            algo->pos_y = algo->map_y;
        } else {
            algo->pos_y = algo->map_y + 1;
        }
        algo->pos_x = player->x + (algo->pos_y - player->y) * algo->dir_x / algo->dir_y;
    }

    return find_length(player, algo);
}

void raycast(t_game *game, t_player *player, int **grid) {
    t_data algo;
    double ray_angle, length, wall_height;
    int x = 0;
    double fov_rad = FOV * (PI / 180.0);
    algo.angle_increment = fov_rad / WINDOW_WIDTH;

    while (x < WINDOW_WIDTH) {
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
