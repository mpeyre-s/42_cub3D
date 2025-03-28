/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:46:44 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/28 11:05:18 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	do_action(t_game *game)
{
	int	target_block[2];

	target_block[0] = (int)(game->player->x + game->player->dir_x);
	target_block[1] = (int)(game->player->y + game->player->dir_y);
	if (target_block[0] < 0 || target_block[0] >= game->map->width ||
		target_block[1] < 0 || target_block[1] >= game->map->height)
		return;
	if (game->map->grid[target_block[1]][target_block[0]] == 1
		&& game->player->inventory == PICKAXE)
		game->map->grid[target_block[1]][target_block[0]] = 0;
	else if (game->map->grid[target_block[1]][target_block[0]] == 0
		&& game->player->inventory == BLOCK
		&& !(target_block[0] == 0 || target_block[0] == game->map->width - 1
			|| target_block[1] == 0 || target_block[1] == game->map->height - 1))
		game->map->grid[target_block[1]][target_block[0]] = 1;
	update_window(game);
}
