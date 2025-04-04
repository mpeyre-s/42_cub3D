/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:20:52 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/04 13:46:52 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_mlx(t_game *game)
{
	print_keycode_config(game);
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx->mlx, loop_hook, game);
	mlx_hook(game->mlx->win, 17, 1L << 17, close_hook, game);
	msg("Game started...", TRUE, FALSE, 0);
	return (SUCCES);
}

int	destroy_mlx(t_game *game)
{
	if (game->mlx->frames != 1)
	{
		if (game->mlx->img)
			mlx_destroy_image(game->mlx->mlx, game->mlx->img);
		if (game->mlx->win)
			mlx_destroy_window(game->mlx->mlx, game->mlx->win);
	}
	free_textures(game->map, game);
	return (SUCCES);
}
