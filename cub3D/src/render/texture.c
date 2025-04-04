/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeyre-s <mpeyre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:21:29 by spike             #+#    #+#             */
/*   Updated: 2025/04/04 17:03:11 by mpeyre-s         ###   ########.fr       */
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
		print_pixel(game, x, y, game->map->floor_color);
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
