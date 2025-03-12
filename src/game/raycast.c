/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:54:11 by spike             #+#    #+#             */
/*   Updated: 2025/03/12 00:32:38 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void print_test(t_mlx *img)
{
    printf("print_test() called\n");

    int x = 0;
    int y;
    char *pixel;

    while (x < WINDOW_WIDTH)
    {
        printf("Processing column %d\n", x);  // Ajout de debug pour vérifier la colonne
        y = 0;
        while (y < WINDOW_HEIGHT)
        {
			printf("Processing line %d\n", y);
            pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
            if (pixel >= img->addr + y * img->line_length + WINDOW_WIDTH * (img->bits_per_pixel / 8))
            {
                printf("Pixel out of bounds: %p\n", (void *)pixel);
                return;
            }
            *(unsigned int *)pixel = 0x008000;
            y++;
        }
        x++;
    }
    printf("print_test() completed\n");
}


void	print_column(t_mlx *img, int x, double wall_height)
{
	double	remain;
	double	sky;
	int		y;
	char	*pixel;

	remain = WINDOW_HEIGHT - wall_height;
	sky = remain / 2;
	y = 0;

	while (y < (int) sky)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)pixel = SKY;
		y++;
	}
	while (y < wall_height + sky)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)pixel = WALL;
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)pixel = FLOOR;
		y++;
	}
}

double	move_while_no_wall(t_print *algo, int **grid)
{
	while (grid[algo->map_x][algo->map_y] == 0)
	{
		if (algo->real_dist_x >= algo->real_dist_y)
		{
			algo->map_x += algo->steps_x;
			algo->real_dist_x += algo->abs_dist_x;
		}
		else
		{
			algo->map_y += algo->steps_y;
			algo->real_dist_y += algo->abs_dist_y;
		}
	}
	if (algo->real_dist_x > algo->real_dist_y)
		return (algo->real_dist_y);
	else
		return (algo->real_dist_x);
}

void	get_real_dist(t_print *algo, t_player *player)
{
	if (player->dir_x < 0)
	{
		algo->steps_x = -1;
		algo->real_dist_x = (player->x - algo->map_x) * algo->abs_dist_x;
	}
	else
	{
		algo->steps_x = 1;
		algo->real_dist_x = (algo->map_x + 1 - player->x) * algo->abs_dist_x;
	}
	if (player->dir_y < 0)
	{
		algo->steps_y = -1;
		algo->real_dist_y = (player->y - algo->map_y) * algo->abs_dist_y;
	}
	else
	{
		algo->steps_y = 1;
		algo->real_dist_y = (algo->map_y + 1 - player->y) * algo->abs_dist_y;
	}
}

double	dda(t_player *player, int **grid, t_print *algo)
{
	double	length;

	algo->map_x = (int)player->x;
	algo->map_y = (int)player->y;

	if (algo->dir_x == 0)
		algo->dir_x = 1e-30;
	if (algo->dir_y == 0)
		algo->dir_y = 1e-30;

	algo->abs_dist_x = fabs(1 / player->dir_x);
	algo->abs_dist_y = fabs(1 / player->dir_y);

	get_real_dist(algo, player);
	length = move_while_no_wall(algo, grid);
	return (length);
}

void	raycast(t_mlx *img, t_player *player, int **grid)
{
	t_print	algo;
	double	ray_angle;
	double	length;
	double	wall_height;
	int		x;

	algo.angle_increment = FOV / WINDOW_WIDTH;
	x = 0;

	while (x < WINDOW_WIDTH)
	{
		ray_angle = player->rotation - (FOV / 2) + (x * algo.angle_increment);
		algo.dir_x = cos(ray_angle);
		algo.dir_y = sin(ray_angle);
		length = dda(player, grid, &algo);
		algo.correct_distance = length * cos(ray_angle - player->rotation);
		wall_height = (WINDOW_HEIGHT / algo.correct_distance) * WINDOW_WIDTH;
		print_column(img, x, wall_height);
		x++;
	}
}


