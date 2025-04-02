/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:49:26 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/02 16:15:42 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	print_pixel(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		pixel = game->mlx->addr + (y * game->mlx->line_length + x
				* (game->mlx->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

void	draw_sqr_minmap(t_game *game, int *coords, int size, int color)
{
	int		x;
	int		y;
	int		end_x;
	int		end_y;

	y = coords[1];
	end_y = coords[1] + size;
	while (y < end_y)
	{
		x = coords[0];
		end_x = coords[0] + size;
		while (x < end_x)
		{
			if ((x > WINDOW_WIDTH / 50 && x < WINDOW_WIDTH / 50
					+ WINDOW_WIDTH / 6) && (y > WINDOW_WIDTH / 50
					&& y < WINDOW_WIDTH / 50 + WINDOW_WIDTH / 6))
				print_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_game *game, int *start, int *end, int color)
{
	int	x;
	int	y;

	y = start[1];
	while (y <= end[1])
	{
		x = start[0];
		while (x <= end[0])
		{
			print_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	color_fill(t_game *game, unsigned int color)
{
	int	x;
	int	y;

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

void	draw_line(t_game *game, int *start, int *end)
{
	int	inc[2];
	int	x;
	int	y;
	int	steps;
	int	i;

	steps = get_steps_and_increments(start, end, inc);
	x = start[0] * 1000;
	y = start[1] * 1000;
	i = 0;
	while (i <= steps * 0.9)
	{
		print_pixel(game, x / 1000, y / 1000,
			invert_color(game->map->floor_color));
		x += inc[0];
		y += inc[1];
		i++;
	}
}
