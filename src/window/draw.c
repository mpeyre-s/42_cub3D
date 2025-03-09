/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:49:26 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/09 18:50:24 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_square(t_game *game, int start_x, int start_y, int size)
{
	int		x;
	int		y;
	char	*pixel;
	int		end_x;
	int		end_y;

	y = start_y;
	end_y = start_y + size;
	while (y < end_y)
	{
		x = start_x;
		end_x = start_x + size;
		while (x < end_x)
		{
			pixel = game->mlx->addr + (y * game->mlx->line_length + x
					* (game->mlx->bits_per_pixel / 8));
			*(unsigned int *)pixel = 0x000000;
			x++;
		}
		y++;
	}
}

void	draw_ellipse(t_game *game, int start_x, int start_y, int size)
{
	int		x;
	int		y;
	char	*pixel;
	int		radius;
	int		center_x;
	int		center_y;

	radius = size / 2;
	center_x = start_x + radius;
	center_y = start_y + radius;
	y = start_y;
	while (y < start_y + size)
	{
		x = start_x;
		while (x < start_x + size)
		{
			if (((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)) <= (radius * radius))
			{
				pixel = game->mlx->addr + (y * game->mlx->line_length + x
						* (game->mlx->bits_per_pixel / 8));
				*(unsigned int *)pixel = 0x00FF00;
			}
			x++;
		}
		y++;
	}
}

void	fill_white_background(t_game *game)
{
	color_fill(game, 0xFFFFFF);
}

void	color_fill(t_game *game, unsigned int color)
{
	int		x;
	int		y;
	char	*pixel;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel = game->mlx->addr + (y * game->mlx->line_length + x
					* (game->mlx->bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
			x++;
		}
		y++;
	}
}

// c'est pas moi qui ait fait cette fonction c'était trop dur de toute ƒacon c'est que visuel et temporaire ˆˆ
void	draw_line(t_game *game, int pixel_x, int pixel_y, int dir_end_x, int dir_end_y, unsigned int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_increment;
	float	y_increment;
	float	x;
	float	y;
	int		i;
	char	*pixel;

	dx = dir_end_x - pixel_x;
	dy = dir_end_y - pixel_y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x_increment = dx / (float)steps;
	y_increment = dy / (float)steps;
	x = pixel_x;
	y = pixel_y;
	i = 0;
	while (i <= steps)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			pixel = game->mlx->addr + ((int)y * game->mlx->line_length + (int)x
					* (game->mlx->bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
		}
		x += x_increment;
		y += y_increment;
		i++;
	}
}
