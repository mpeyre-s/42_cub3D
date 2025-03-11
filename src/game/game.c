/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:18:21 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/11 18:25:49 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_game(t_game *game)
{
	start_mlx(game);

	update_map(game);
	mlx_loop(game->mlx->mlx);
	return (0);
}

void	update_map(t_game *game)
{
	//color_fill(game, 0xFFFFFF);
	raycast(game->mlx, game->player, game->map->grid);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img, 0, 0);
}
