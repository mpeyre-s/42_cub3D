/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:29:21 by spike             #+#    #+#             */
/*   Updated: 2025/03/29 09:13:32 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	select_floor_txt(int y, int x, t_floor *floor, t_txt *texture, t_player *player)
{
	int	pxl_x;
	int	pxl_y;
	int color;

	floor->dy = (P_SIZE * floor->dproj) / (y - (WINDOW_HEIGHT / 2));
	floor->dir_x1 = player->dir_x - player->plane_x;
	floor->dir_x2 = player->dir_x + player->plane_x;
	floor->dir_y1 = player->dir_y - player->plane_y;
	floor->dir_y2 = player->dir_y + player->plane_y;

	floor->floor_x = player->x + floor->dy * (floor->dir_x1 + (x / (double)WINDOW_WIDTH) * (floor->dir_x2 - floor->dir_x1));
	floor->floor_y = player->y + floor->dy * (floor->dir_y1 + (x / (double)WINDOW_WIDTH) * (floor->dir_y2 - floor->dir_y1));

	pxl_x = (int)(floor->floor_x * 64) % 64;
	pxl_y = (int)(floor->floor_y * 64) % 64;

	color = get_pixel_from_texture(texture, pxl_x, pxl_y);
	return (color);
}

