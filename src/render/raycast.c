/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:19:56 by spike             #+#    #+#             */
/*   Updated: 2025/03/31 15:26:15 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_len_ray(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
		ray->len_x = (player->x - ray->m_x) * ray->delta_dist_x;
	else
		ray->len_x = (ray->m_x + 1.0 - player->x) * ray->delta_dist_x;


	if (ray->dir_y < 0)
		ray->len_y = (player->y - ray->m_y) * ray->delta_dist_y;
	else
		ray->len_y = (ray->m_y + 1.0 - player->y) * ray->delta_dist_y;
}

void	init_ray(int x, t_ray *ray, t_player *player)
{
	ft_memset(ray, 0, sizeof(t_ray));
	ray->m_x = (int) player->x;
	ray->m_y = (int) player->y;

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
			ray->m_x += ray->step_x;
			ray->len_x += ray->delta_dist_x;
			if (ray->step_x > 0)
				ray->hit_side = 1;
			else
				ray->hit_side = 2;
		}
		else
		{
			ray->m_y += ray->step_y;
			ray->len_y += ray->delta_dist_y;
			if (ray->step_y > 0)
				ray->hit_side = -1;
			else
				ray->hit_side = -2;
		}
		if (ray->m_y < 0 || ray->m_x < 0)
			break ;
		if (grid[ray->m_y][ray->m_x] == 1 || grid[ray->m_y][ray->m_x] == 2)
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

	if (ray->hit_side == 1 || ray->hit_side == 2)
		ray->wall_norm_x = player->y + ray->wall_dist * ray->dir_y;
	else
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
