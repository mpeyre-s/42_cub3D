/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:18:21 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/25 19:21:28 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_game(t_game *game)
{
	start_mlx(game);
	mlx_clear_window(game->mlx->mlx, game->mlx->win);
	update_map(game);
	mlx_loop(game->mlx->mlx);
	return (0);
}

void	update_map(t_game *game)
{
	raycast(game, game->player, game->map->grid);
	print_minimap(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img, 0, 0);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->gun_texture.img,  // Image de l'arme
		WINDOW_WIDTH - game->gun_texture.width,  // Position horizontale à droite
		WINDOW_HEIGHT - game->gun_texture.height); // Position verticale en bas
}


