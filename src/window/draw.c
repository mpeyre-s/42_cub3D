/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:49:26 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/15 19:58:30 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	print_pixel(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		pixel = game->mlx->addr + (y * game->mlx->line_length + x *
				(game->mlx->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

void	draw_square(t_game *game, int start_x, int start_y, int size)
{
	int		x;
	int		y;
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
			print_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_ellipse(t_game *game, int start_x, int start_y, int size)
{
	int		x;
	int		y;
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
				print_pixel(game, x, y, 0x00FF00);
			x++;
		}
		y++;
	}
}

void	color_fill(t_game *game, unsigned int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			print_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_line(t_game *game, int pixel_x, int pixel_y,
		int dir_end_x, int dir_end_y, unsigned int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_increment;
	float	y_increment;
	float	x;
	float	y;
	int		i;

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
			print_pixel(game, x, y, color);
		x += x_increment;
		y += y_increment;
		i++;
	}
}
