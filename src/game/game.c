/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:18:21 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/09 00:56:17 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_game(t_game *game)
{
	start_mlx(game);
	// game here
	update_window(game, fill_white_background);
	update_window(game, print_grid);
	mlx_loop(game->mlx);
	return (0);
}

void	print_grid(t_game *game)
{
	int		x;
	int		y;
	int		grid_width;
	int		grid_height;
	char	*pixel;

	grid_width = game->map->cell_width * game->map->width;
	grid_height = game->map->cell_height * game->map->height;
	y = game->map->cell_height;
	while (y <= grid_height)
	{
		x = 0;
		while (x < grid_width)
		{
			pixel = game->mlx->addr + (y * game->mlx->line_length + x
				* (game->mlx->bits_per_pixel / 8));
			*(unsigned int *)pixel = 0x000000;
			x++;
		}
		y += game->map->cell_height;
	}
	x = game->map->cell_width;
	while (x <= grid_width)
	{
		y = 0;
		while (y < grid_height)
		{
			pixel = game->mlx->addr + (y * game->mlx->line_length + x
				* (game->mlx->bits_per_pixel / 8));
			*(unsigned int *)pixel = 0x000000;
			y++;
		}
		x += game->map->cell_width;
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
