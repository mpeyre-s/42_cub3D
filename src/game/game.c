/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:18:21 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/28 08:56:55 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_game(t_game *game)
{
	start_mlx(game);
	mlx_clear_window(game->mlx->mlx, game->mlx->win);
	update_window(game);
	mlx_loop(game->mlx->mlx);
	return (0);
}

void	update_window(t_game *game)
{
	raycast(game, game->player, game->map->grid);
	print_minimap(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img, 0, 0);
	if (game->player->inventory == PICKAXE)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
			game->pickaxe_hud.img, 0, 0);
	else if (game->player->inventory == BLOCK)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
			game->block_hud.img, 0, 0);
}
