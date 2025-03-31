/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:21:29 by spike             #+#    #+#             */
/*   Updated: 2025/03/31 15:25:00 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_pixel_from_texture(t_txt *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);

	pixel = (char *)texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(int *)pixel;

	return (color);
}

int	select_texture_pixel(int y, t_txt *texture, t_ray *ray)
{
	int		pixel_x;
	int		pixel_y;
	int		color;
	double	texture_offset;

	pixel_x = (int)(ray->wall_norm_x * texture->width);
	if (pixel_x < 0)
		pixel_x = 0;
	if (pixel_x >= texture->width)
		pixel_x = texture->width - 1;

	texture_offset = (ray->wall_start - (WINDOW_HEIGHT / 2) + (ray->pxl_height / 2));
	pixel_y = (int)((texture_offset + (y - ray->wall_start)) / ray->pxl_height * texture->height);
	if (pixel_y < 0)
		pixel_y = 0;
	if (pixel_y >= texture->height)
		pixel_y = texture->height - 1;

	color = get_pixel_from_texture(texture, pixel_x, pixel_y);

	return (color);
}


int	select_floor_txt(int x, int y, t_floor *floor, t_txt *texture, t_player *player)
{
	ft_memset(floor, 0, sizeof(t_floor));

	if (y <= WINDOW_HEIGHT / 2)
		return 0;

	// Direction des rayons pour le bord gauche et droit
	floor->rayDirX0 = player->dir_x - player->plane_x;
	floor->rayDirY0 = player->dir_y - player->plane_y;
	floor->rayDirX1 = player->dir_x + player->plane_x;
	floor->rayDirY1 = player->dir_y + player->plane_y;

	// Position verticale de la caméra
	floor->p = y - WINDOW_HEIGHT / 2;
	floor->posZ = 0.5 * WINDOW_HEIGHT;
	floor->rowDist = floor->posZ / floor->p;

	// Calcul des coordonnées du sol pour ce pixel spécifique (x,y)
	floor->floor_step_x = floor->rowDist * (floor->rayDirX1 - floor->rayDirX0) / WINDOW_WIDTH;
	floor->floor_step_y = floor->rowDist * (floor->rayDirY1 - floor->rayDirY0) / WINDOW_WIDTH;

	floor->floor_x = player->x + floor->rowDist * floor->rayDirX0 + floor->floor_step_x * x;
	floor->floor_y = player->y + floor->rowDist * floor->rayDirY0 + floor->floor_step_y * x;

	// Calcul des coordonnées de texture
	floor->cell_x = (int)(floor->floor_x);
	floor->cell_y = (int)(floor->floor_y);
	floor->tx = (int)(texture->width * (floor->floor_x - floor->cell_x)) & (texture->width - 1);
	floor->ty = (int)(texture->height * (floor->floor_y - floor->cell_y)) & (texture->height - 1);

	return (get_pixel_from_texture(texture, floor->tx, floor->ty));
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
		color = select_floor_txt(x, y, game->floor, &game->map->floors, game->player);
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
