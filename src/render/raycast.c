/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:24:32 by spike             #+#    #+#             */
/*   Updated: 2025/03/21 13:54:17 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

typedef struct s_text
{
	void	*img;
	void	*addr;
}				t_text;

void print_colonne(t_game *game, int x, t_ray *ray)
{
	int start;
	int end;
	int color;

	start = ray->wall_start;
	end = ray->wall_end;

	switch (ray->hit_side)
	{
		case 1:  // EST
			color = 0xFF0000;  // Rouge
			break;
		case 2:  // OUEST
			color = 0xCC0000;  // Rouge foncé
			break;
		case -1: // NORD
			color = 0x0000FF;  // Bleu
			break;
		case -2: // SUD
			color = 0x0000CC;  // Bleu foncé
			break;
		default:
			color = 0xFFFFFF;  // Blanc par défaut
	}

	int y = 0;
	while (y < start)
	{
		print_pixel(game, x, y, 0x333333);
		y++;
	}

	y = start;
	while (y < end)
	{
		print_pixel(game, x, y, color);
		y++;
	}

	y = end;
	while (y < WINDOW_HEIGHT)
	{

		print_pixel(game, x, y, 0x222222);
		y++;
	}
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
	ray->map_x = (int) player->x;
	ray->map_y = (int) player->y;

	ray->camera_x = 2 * x / WINDOW_WIDTH - 1;
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
				ray->hit_side = 1; // EST
			else
				ray->hit_side = 2; // WEST
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->len_y += ray->delta_dist_y;
			if (ray->step_y > 0)
				ray->hit_side = -1; // NORTH
			else
				ray->hit_side = -2; // SOUTH
		}
		if (grid[ray->map_x][ray->map_y] == 1)
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

	if (ray->hit_side > 0)
		ray->wall_hit = player->y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_hit = player->x + ray->wall_dist * ray->dir_x;

	ray->wall_hit -= floor(ray->wall_hit);
}

void raycast(t_game *game, t_player *player, int **grid)
{
	t_ray	ray;
	t_text	txt;
	int x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(x, &ray, player);
		dda_algo(&ray, grid);
		wall_ray_size(&ray, player);
		print_colonne(game, x, &ray);
		render_with_text(game, &txt, &ray);
		x++;
	}
}
