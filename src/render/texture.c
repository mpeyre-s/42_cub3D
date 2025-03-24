/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:21:29 by spike             #+#    #+#             */
/*   Updated: 2025/03/24 11:56:04 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_tex_x(t_map *map, t_ray *ray)
{
	if (ray->hit_side == -1)
		map->north.tex_x = (int)(ray->wall_norm_x * map->north.width);
	else if (ray->hit_side == -2)
		map->south.tex_x = (int)(ray->wall_norm_x * map->south.width);
	else if (ray->hit_side == 1)
		map->east.tex_x = (int)(ray->wall_norm_x * map->east.width);
	else if (ray->hit_side == 2)
		map->west.tex_x = (int)(ray->wall_norm_x * map->west.width);
}

void	render_texture(int x, t_game *game, t_txt *texture, t_ray *ray)
{
	//double	step;
	int		y;
	//double	tex_pos;

	//step = texture->height / ray->pxl_height;
	(void)texture;
	y = 0;
	//tex_pos = 0;
	while (y < ray->wall_start)
	{
		print_pixel(game, x, y, 0x333333);
		y++;
	}

	y = ray->wall_start;
	while (y < ray->wall_end)
	{
		print_pixel(game, x, y, 0x0000CC);
		y++;
	}

	y = ray->wall_end;
	while (y < WINDOW_HEIGHT)
	{
		print_pixel(game, x, y, 0x222222);
		y++;
	}
}

void	handle_txt(int x, t_map *map, t_game *game, t_ray *ray)
{
	init_tex_x(map, ray);
	if (ray->hit_side == -1)
		render_texture(x, game, &(map->south), ray);
	else if (ray->hit_side == -2)
		render_texture(x, game, &(map->north), ray);
	else if (ray->hit_side == 1)
		render_texture(x, game, &(map->west), ray);
	else if (ray->hit_side == 2)
		render_texture(x, game, &(map->east), ray);
}
