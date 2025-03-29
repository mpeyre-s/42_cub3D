/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:19:56 by spike             #+#    #+#             */
/*   Updated: 2025/03/29 08:50:21 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	info(t_ray *ray, t_player *player)
{
	printf("Info :\n");
	printf("	Joueur :\n");
	printf("		Position : (%f, %f)\n", player->x, player->y);
	printf("		Direction : (%f, %f)\n", player->dir_x, player->dir_y);
	printf("		Plan : (%f, %f)\n", player->plane_x, player->plane_y);
	printf("		Rotation : %f\n", player->rotation);
	printf("		Orientation : %c\n", player->direction);
	printf("\n");
	printf("	Ray :\n");
	printf("		Map pos : (%d, %d)\n", ray->map_x, ray->map_y);
	printf("		Camera X : %f\n", ray->camera_x);
	printf("		Direction : (%f, %f)\n", ray->dir_x, ray->dir_y);
	printf("		Length X/Y : (%f, %f)\n", ray->len_x, ray->len_y);
	printf("		Delta dist X/Y : (%f, %f)\n", ray->delta_dist_x, ray->delta_dist_y);
	printf("		Step X/Y : (%d, %d)\n", ray->step_x, ray->step_y);
	printf("		Wall distance : %f\n", ray->wall_dist);
	printf("		Pixel height : %d\n", ray->pxl_height);
	printf("		Wall start/end : (%d, %d)\n", ray->wall_start, ray->wall_end);
	printf("		Wall hit position : %f\n", ray->wall_norm_x);
	printf("		Hit side : %d\n", ray->hit_side);
}

void	set_to_zero(t_ray *ray)
{
	ray->map_x = 0;
	ray->map_y = 0;
	ray->camera_x = 0.0;
	ray->dir_x = 0.0;
	ray->dir_y = 0.0;
	ray->len_x = 0.0;
	ray->len_y = 0.0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit_side = 0;
	ray->wall_dist = 0.0;
	ray->pxl_height = 0;
	ray->wall_start = 0;
	ray->wall_end = 0;
	ray->wall_norm_x = 0.0;
}

void	init_len_ray(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
		ray->len_x = (player->x - ray->map_x) * ray->delta_dist_x;
	else
		ray->len_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;


	if (ray->dir_y < 0)
		ray->len_y = (player->y - ray->map_y) * ray->delta_dist_y;
	else
		ray->len_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
}

void	init_ray(int x, t_ray *ray, t_player *player)
{
	set_to_zero(ray);
	ray->map_x = (int) player->x;
	ray->map_y = (int) player->y;

	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;

	if (fabs(ray->dir_x) < 1e-6)
		ray->dir_x = 1e-6;
	if (fabs(ray->dir_y) < 1e-6)
		ray->dir_y = 1e-6;

	ray->delta_dist_x = 1/fabs(ray->dir_x);
	ray->delta_dist_y = 1/fabs(ray->dir_y);

	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;

	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;

	init_len_ray(ray, player);
}


void	dda_algo(t_ray *ray, int **grid)
{
	while (1)
	{
		if (ray->len_x < ray->len_y)
		{
			ray->map_x += ray->step_x;
			ray->len_x += ray->delta_dist_x;
			if (ray->step_x > 0)
				ray->hit_side = 1; // WEST
			else
				ray->hit_side = 2; // EAST
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->len_y += ray->delta_dist_y;
			if (ray->step_y > 0)
				ray->hit_side = -1; // South
			else
				ray->hit_side = -2; // North
		}
		if (ray->map_y < 0 || ray->map_x < 0
			|| ray->map_y > 100
			|| ray->map_x > 100)
			break ;
		if (grid[ray->map_y][ray->map_x] == 1
			|| grid[ray->map_y][ray->map_x] == 2)
			break;
	}
}

void	wall_ray_size(t_ray *ray, t_player *player)
{
	if (ray->hit_side > 0)
		ray->wall_dist = (ray->len_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->len_y - ray->delta_dist_y);

	ray->pxl_height = (int)(WINDOW_HEIGHT / ray->wall_dist);

	ray->wall_start = (int)((WINDOW_HEIGHT / 2) - (ray->pxl_height / 2));
	if (ray->wall_start < 0)
		ray->wall_start = 0;

	ray->wall_end = (int)((WINDOW_HEIGHT / 2) + (ray->pxl_height / 2));
	if (ray->wall_end >= WINDOW_HEIGHT)
		ray->wall_end = WINDOW_HEIGHT - 1;

	if (ray->hit_side == 1 || ray->hit_side == 2) // Mur Est/Ouest
		ray->wall_norm_x = player->y + ray->wall_dist * ray->dir_y;
	else // Mur Nord/Sud
		ray->wall_norm_x = player->x + ray->wall_dist * ray->dir_x;

	ray->wall_norm_x -= floor(ray->wall_norm_x);
}

void raycast(t_game *game, t_player *player, int **grid)
{
	t_ray	ray;
	int x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(x, &ray, player);
		dda_algo(&ray, grid);
		wall_ray_size(&ray, player);
		handle_txt(x, game->map, game, &ray);
		x++;
	}
}
