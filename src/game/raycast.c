/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:10:33 by spike             #+#    #+#             */
/*   Updated: 2025/03/18 18:02:00 by spike            ###   ########.fr       */
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

double find_length(t_player *player, t_data *algo)
{
    double wall_dist;
	(void)player;
    //double correction_factor;

	if (algo->len_x < algo->len_y)
		wall_dist = algo->len_x;
	else
		wall_dist = algo->len_y;

	double correction_factor = fabs(player->dir_x * algo->dir_x + player->dir_y * algo->dir_y);
	wall_dist *= correction_factor;

	printf("Wall dist = %f // len x = %f // len y = %f\n", wall_dist, algo->len_x, algo->len_y);
	printf("map_x = %d, map_y = %d\n", algo->map_x, algo->map_y);
	printf("dir_x = %f\n", algo->dir_x);
	printf("dir_y = %f\n", algo->dir_y);

    // Assurer que la distance est positive
    wall_dist = fabs(wall_dist);

    return wall_dist;
}


void set_hypoth(t_data *algo)
{
    if (algo->dir_x > 0)
        algo->len_x = (algo->map_x + 1.0 - algo->pos_x) / algo->dir_x;
    else if (algo->dir_x < 0)
        algo->len_x = (algo->map_x - algo->pos_x) / algo->dir_x;
    else
        algo->len_x = INFINITY;

    if (algo->dir_y > 0)
        algo->len_y = (algo->map_y + 1.0 - algo->pos_y) / algo->dir_y;
    else if (algo->dir_y < 0)
        algo->len_y = (algo->map_y - algo->pos_y) / algo->dir_y;
    else
        algo->len_y = INFINITY;

    // Assurer que les distances sont positives (important!)
    algo->len_x = fabs(algo->len_x);
    algo->len_y = fabs(algo->len_y);
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

	algo->delta_dist_x = (algo->dir_x != 0) ? fabs(1 / algo->dir_x) : INFINITY;
	algo->delta_dist_y = (algo->dir_y != 0) ? fabs(1 / algo->dir_y) : INFINITY;

}

double	dda_algo(t_player *player, t_data *algo, int **grid)
{
	init_data(player, algo);
	set_hypoth(algo);

	while (1)
	{
		print_algo_data(algo);
		if (algo->len_x < algo->len_y)
		{
			// On avance dans la direction X
			algo->map_x += algo->step_x;
			algo->len_x += algo->delta_dist_x; // On avance vers la prochaine frontière verticale
		}
		else
		{
			// On avance dans la direction Y
			algo->map_y += algo->step_y;
			algo->len_y += algo->delta_dist_y; // On avance vers la prochaine frontière horizontale
		}
		if (grid[algo->map_x][algo->map_y] == 1)
		{
			printf("grid[%d][%d]\n\n", algo->map_x, algo->map_y);
			break ;
		}
		printf("grid[%d][%d]\n\n", algo->map_x, algo->map_y);
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
		printf("pixel x = %d\nwall_height = %f\n", x, wall_height);
	}
}
