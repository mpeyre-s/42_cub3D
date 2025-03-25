/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:46:30 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/25 18:39:56 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


static void	print_player_direction(t_game *game, int *start_dir, int *end_dir)
{
	int	offset;
	int	adjusted_start[2];
	int	adjusted_end[2];

	offset = -2;
	while (++offset <= 1)
	{
		adjusted_start[0] = start_dir[0] + offset;
		adjusted_start[1] = start_dir[1];
		adjusted_end[0] = end_dir[0] + offset;
		adjusted_end[1] = end_dir[1];
		draw_line(game, adjusted_start, adjusted_end);
		adjusted_start[0] = start_dir[0];
		adjusted_start[1] = start_dir[1] + offset;
		adjusted_end[0] = end_dir[0];
		adjusted_end[1] = end_dir[1] + offset;
		draw_line(game, adjusted_start, adjusted_end);
	}
}

static void	print_player(t_game *game)
{
	int	player_pos[2];
	int	player_end[2];
	int	player_size;
	int	start_dir[2];
	int	end_dir[2];

	player_size = WINDOW_WIDTH / 100;
	player_pos[0] = (WINDOW_WIDTH / 50) + ((WINDOW_WIDTH / 6) / 2)
		- (player_size / 2);
	player_pos[1] = (WINDOW_WIDTH / 50) + ((WINDOW_WIDTH / 6) / 2)
		- (player_size / 2);
	player_end[0] = player_pos[0] + player_size - 1;
	player_end[1] = player_pos[1] + player_size - 1;
	draw_rectangle(game, player_pos, player_end, invert_color(game->map->floor_color));
	start_dir[0] = player_pos[0] + (player_size / 2);
	start_dir[1] = player_pos[1] + (player_size / 2);
	end_dir[0] = start_dir[0] + (game->player->dir_x * 20);
	end_dir[1] = start_dir[1] + (game->player->dir_y * 20);
	draw_line(game, start_dir, end_dir);
	print_player_direction(game, start_dir, end_dir);
}

static int	get_cell_color(t_game *game, int grid_x, int grid_y)
{
	if (grid_x >= 0 && grid_x < game->map->width &&
		grid_y >= 0 && grid_y < game->map->height &&
		game->map->grid[grid_y][grid_x] == 1)
		return (0x000000);
	return (game->map->floor_color);
}


static void	draw_cell(t_game *game, int grid_x, int grid_y, int cell_size)
{
	int		coords[2];
	float	player_x;
	float	player_y;
	float	offset_x;
	float	offset_y;

	player_x = game->player->x;
	player_y = game->player->y;
	offset_x = player_x - floor(player_x) - 0.5;
	offset_y = player_y - floor(player_y) - 0.5;

	coords[0] = (WINDOW_WIDTH / 50) + ((grid_x - floor(player_x)) - offset_x + 2) * cell_size;
	coords[1] = (WINDOW_WIDTH / 50) + ((grid_y - floor(player_y)) - offset_y + 2) * cell_size;
	draw_square_minimap(game, coords, cell_size, get_cell_color(game, grid_x, grid_y));
}

static void	draw_minimap_grid(t_game *game, int cell_size)
{
	int		i;
	int		j;
	float	player_x;
	float	player_y;
	int		grid_x;
	int		grid_y;

	player_x = game->player->x;
	player_y = game->player->y;
	i = -4;
	while (++i <= 3)
	{
		j = -4;
		while (++j <= 3)
		{
			grid_x = floor(player_x) + j;
			grid_y = floor(player_y) + i;
			draw_cell(game, grid_x, grid_y, cell_size);
		}
	}
}

void	print_minimap(t_game *game)
{
	int	cell_size;

	cell_size = (WINDOW_WIDTH / 6) / 5;
	draw_minimap_grid(game, cell_size);

	print_player(game);
}
