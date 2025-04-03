/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:21:29 by spike             #+#    #+#             */
/*   Updated: 2025/04/02 14:40:08 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	select_texture_pixel(int y, t_txt *texture, t_ray *r)
{
	int		pixel_x;
	int		pixel_y;
	int		color;
	double	t_offset;

	pixel_x = (int)(r->wall_norm_x * texture->width);
	if (pixel_x < 0)
		pixel_x = 0;
	if (pixel_x >= texture->width)
		pixel_x = texture->width - 1;
	t_offset = (r->wall_start - (WINDOW_HEIGHT / 2) + (r->pxl_height / 2));
	pixel_y = (int)((t_offset
				+ (y - r->wall_start)) / r->pxl_height * texture->height);
	if (pixel_y < 0)
		pixel_y = 0;
	if (pixel_y >= texture->height)
		pixel_y = texture->height - 1;
	color = get_pixel_from_texture(texture, pixel_x, pixel_y);
	return (color);
}

void	calculate_floor(int y, t_floor *floor, t_player *player)
{
	floor->ray_dir_x0 = player->dir_x - player->plane_x;
	floor->ray_dir_y0 = player->dir_y - player->plane_y;
	floor->ray_dir_x1 = player->dir_x + player->plane_x;
	floor->ray_dir_y1 = player->dir_y + player->plane_y;
	floor->p = y - WINDOW_HEIGHT / 2;
	floor->pos = 0.5 * WINDOW_HEIGHT;
	floor->row_dist = floor->pos / floor->p;
}

int	select_floor_txt(int x, int y, t_game *game, t_txt *t)
{
	t_player	*player;
	t_floor		*floor;

	player = game->player;
	floor = game->floor;
	ft_memset(floor, 0, sizeof(t_floor));
	if (y <= WINDOW_HEIGHT / 2)
		return (0);
	calculate_floor(y, floor, player);
	floor->floor_step_x = floor->row_dist
		* (floor->ray_dir_x1 - floor->ray_dir_x0) / WINDOW_WIDTH;
	floor->floor_step_y = floor->row_dist
		* (floor->ray_dir_y1 - floor->ray_dir_y0) / WINDOW_WIDTH;
	floor->floor_x = player->x + floor->row_dist
		* floor->ray_dir_x0 + floor->floor_step_x * x;
	floor->floor_y = player->y + floor->row_dist
		* floor->ray_dir_y0 + floor->floor_step_y * x;
	floor->cell_x = (int)(floor->floor_x);
	floor->cell_y = (int)(floor->floor_y);
	floor->tx = (int)(t->width * (floor->floor_x - floor->cell_x))
		& (t->width - 1);
	floor->ty = (int)(t->height * (floor->floor_y - floor->cell_y))
		& (t->height - 1);
	return (get_pixel_from_texture(t, floor->tx, floor->ty));
}

void	render_texture(int x, t_game *game, t_txt *texture, t_ray *ray)
{
	int		y;
	int		color;

	y = 0;
	while (y < ray->wall_start)
	{
		print_pixel(game, x, y, game->map->sky_color);
		y++;
	}
	y = ray->wall_start;
	while (y < ray->wall_end)
	{
		color = select_texture_pixel(y, texture, ray);
		print_pixel(game, x, y, color);
		y++;
	}
	y = ray->wall_end;
	while (y < WINDOW_HEIGHT)
	{
		color = select_floor_txt(x, y, game, &game->map->floors);
		print_pixel(game, x, y, color);
		y++;
	}
}

void	handle_txt(int x, t_map *map, t_game *game, t_ray *ray)
{
	if (ray->hit_side == -1)
		render_texture(x, game, &(map->south), ray);
	else if (ray->hit_side == -2)
		render_texture(x, game, &(map->north), ray);
	else if (ray->hit_side == 1)
		render_texture(x, game, &(map->west), ray);
	else if (ray->hit_side == 2)
		render_texture(x, game, &(map->east), ray);
}
