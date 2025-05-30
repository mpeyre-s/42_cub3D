/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeyre-s <mpeyre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:24 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/04 15:10:29 by mpeyre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == MAC_ESC_KEY || keycode == LIN_ESC_KEY)
		close_hook(game);
	else if (keycode == MAC_FORWARD_KEY || keycode == LIN_FORWARD_KEY)
		game->keys->forward = 1;
	else if (keycode == MAC_BACKWARD_KEY || keycode == LIN_BACKWARD_KEY)
		game->keys->backward = 1;
	else if (keycode == MAC_LEFT_KEY || keycode == LIN_LEFT_KEY)
		game->keys->left = 1;
	else if (keycode == MAC_RIGHT_KEY || keycode == LIN_RIGHT_KEY)
		game->keys->right = 1;
	else if (keycode == MAC_LEFT_ARROW || keycode == LIN_LEFT_ARROW)
		game->keys->rotate_left = 1;
	else if (keycode == MAC_RIGHT_ARROW || keycode == LIN_RIGHT_ARROW)
		game->keys->rotate_right = 1;
	else if (keycode == MAC_UP_KEY || keycode == LIN_UP_KEY)
		game->keys->action = 1;
	else if (keycode == MAC_1_EXCLA || keycode == LIN_1_EXCLA)
		game->player->inventory = PICKAXE;
	else if (keycode == MAC_2_AROBAS || keycode == LIN_2_AROBAS)
		game->player->inventory = BLOCK;
	if (keycode == MAC_1_EXCLA || keycode == LIN_1_EXCLA
		|| keycode == MAC_2_AROBAS || keycode == LIN_2_AROBAS)
		update_window(game);
	game->mlx->frames = 2;
	return (SUCCES);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == MAC_ESC_KEY || keycode == LIN_ESC_KEY)
		close_hook(game);
	else if (keycode == MAC_FORWARD_KEY || keycode == LIN_FORWARD_KEY)
		game->keys->forward = 0;
	else if (keycode == MAC_BACKWARD_KEY || keycode == LIN_BACKWARD_KEY)
		game->keys->backward = 0;
	else if (keycode == MAC_LEFT_KEY || keycode == LIN_LEFT_KEY)
		game->keys->left = 0;
	else if (keycode == MAC_RIGHT_KEY || keycode == LIN_RIGHT_KEY)
		game->keys->right = 0;
	else if (keycode == MAC_LEFT_ARROW || keycode == LIN_LEFT_ARROW)
		game->keys->rotate_left = 0;
	else if (keycode == MAC_RIGHT_ARROW || keycode == LIN_RIGHT_ARROW)
		game->keys->rotate_right = 0;
	else if (keycode == MAC_UP_KEY || keycode == LIN_UP_KEY)
		game->keys->action = 0;
	return (SUCCES);
}

int	loop_hook(t_game *game)
{
	if (game->keys->forward)
		move_player(game, FOWARD);
	if (game->keys->backward)
		move_player(game, BACKWARD);
	if (game->keys->left)
		move_player(game, LEFT);
	if (game->keys->right)
		move_player(game, RIGHT);
	if (game->keys->rotate_left)
		rotate_player(game, TURN_LEFT);
	if (game->keys->rotate_right)
		rotate_player(game, TURN_RIGHT);
	if (game->keys->action)
		do_action(game);
	return (SUCCES);
}

int	close_hook(t_game *game)
{
	exit_program(game);
	msg("Exit...", TRUE, FALSE, EXIT_SUCCESS);
	exit(SUCCES);
}
