/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:20:52 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/07 17:28:00 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_mlx(t_game *game)
{
	mlx_hook(game->mlx->win, 2, 1L << 0, key_hook, &game);
	mlx_hook(game->mlx->win, 17, 1L << 17, close_hook, &game);
	mlx_loop(game->mlx);
	return (SUCCES);
}

int	destroy_mlx(t_game *game)
{
	if (!game)
		return (0);
	if (game->mlx->img)
		mlx_destroy_image(game->mlx->mlx, game->mlx->img);
	if (game->mlx->win)
		mlx_destroy_image(game->mlx->mlx, game->mlx->win);
	// if (game->mlx->mlx)
	// {
	// 	mlx_destroy_display(game->mlx->mlx);
	// 	free(game->mlx->mlx);
	// }
	return (SUCCES);
}

