/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:46:30 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/09 18:44:38 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	fill_grid_with_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->grid[i][j] == 1)
				draw_square(game, j * game->map->cell_width,
					i * game->map->cell_height,
					game->map->cell_width);
			j++;
		}
		i++;
	}
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

void	spawn_player(t_game *game)
{
	int	pixel_x;
	int	pixel_y;
	int	dir_end_x;
	int	dir_end_y;

	pixel_x = (int)(game->player->x * game->map->cell_width);
	pixel_y = (int)(game->player->y * game->map->cell_height);
	draw_ellipse(game, pixel_x - 10, pixel_y - 10, 21);

	dir_end_x = pixel_x + (int)(game->player->dir_x * 20);
	dir_end_y = pixel_y + (int)(game->player->dir_y * 20);
	draw_line(game, pixel_x, pixel_y, dir_end_x, dir_end_y, 0xFF0000);
}
