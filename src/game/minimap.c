/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:46:30 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/23 13:00:18 by mathispeyre      ###   ########.fr       */
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
	int	player_size;
	int	start_dir[2];
	int	end_dir[2];

	player_size = WINDOW_WIDTH / 200;
	player_pos[0] = (WINDOW_WIDTH / 50) + ((WINDOW_WIDTH / 6) / 2)
		- (player_size / 2);
	player_pos[1] = (WINDOW_WIDTH / 50) + ((WINDOW_WIDTH / 6) / 2)
		- (player_size / 2);
	draw_square(game, player_pos, player_size, 0xFFFFFF);
	start_dir[0] = player_pos[0] + (player_size / 2);
	start_dir[1] = player_pos[1] + (player_size / 2);
	end_dir[0] = start_dir[0] + (game->player->dir_x * 20);
	end_dir[1] = start_dir[1] + (game->player->dir_y * 20);
	draw_line(game, start_dir, end_dir);
	print_player_direction(game, start_dir, end_dir);
}

void	print_minimap(t_game *game)
{
	int	coords[2];

	coords[0] = WINDOW_WIDTH / 50;
	coords[1] = WINDOW_WIDTH / 50;
	draw_square(game, coords, WINDOW_WIDTH / 6, 0x32506C);
	// print squares (5x5 : 4 cells around player + center)
	print_player(game);
}
