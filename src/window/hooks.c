/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:24 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/09 17:56:20 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_hook(int keycode, t_game *game)
{
	if (game->mlx->os == LINUX)
		linux_key_hook(keycode, game);
	else if (game->mlx->os == MACOS)
		macos_key_hook(keycode, game);
	return (SUCCES);
}

void	linux_key_hook(int keycode, t_game *game)
{
	if (keycode == LIN_ESC_KEY)
		exit_program(game);
	else if (keycode == LIN_FORWARD_KEY)
		move_player(game, FOWARD);
	else if (keycode == LIN_BACKWARD_KEY)
		move_player(game, BACKWARD);
	else if (keycode == LIN_LEFT_KEY)
		move_player(game, LEFT);
	else if (keycode == LIN_RIGHT_KEY)
		move_player(game, RIGHT);
}

void	macos_key_hook(int keycode, t_game *game)
{
	if (keycode == MAC_ESC_KEY)
		exit_program(game);
	else if (keycode == MAC_FORWARD_KEY)
		move_player(game, FOWARD);
	else if (keycode == MAC_BACKWARD_KEY)
		move_player(game, BACKWARD);
	else if (keycode == MAC_LEFT_KEY)
		move_player(game, LEFT);
	else if (keycode == MAC_RIGHT_KEY)
		move_player(game, RIGHT);
}

int	close_hook(t_game *game)
{
	exit_program(game);
	return (SUCCES);
}
