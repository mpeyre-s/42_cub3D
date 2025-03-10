/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:26:26 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/10 16:50:22 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_move_possible(t_game *game, t_action action)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x;
	new_y = game->player->y;
	if (action == FOWARD)
	{
		new_x += game->player->dir_x * MOVE_SPEED;
		new_y += game->player->dir_y * MOVE_SPEED;
	}
	else if (action == BACKWARD)
	{
		new_x -= game->player->dir_x * MOVE_SPEED;
		new_y -= game->player->dir_y * MOVE_SPEED;
	}
	else if (action == LEFT)
	{
		new_x += game->player->dir_y * MOVE_SPEED;
		new_y -= game->player->dir_x * MOVE_SPEED;
	}
	else if (action == RIGHT)
	{
		new_x -= game->player->dir_y * MOVE_SPEED;
		new_y += game->player->dir_x * MOVE_SPEED;
	}
	if (new_x < 0 || new_y < 0 || new_x >= game->map->width || new_y >= game->map->height)
		return (FALSE);
	if (game->map->grid[(int)floor(new_y)][(int)floor(new_x)] == 1)
		return (FALSE);
	return (TRUE);
}

void	move_player(t_game *game, t_action action)
{
	if (action == FOWARD && is_move_possible(game, FOWARD))
	{
		game->player->x += game->player->dir_x * MOVE_SPEED;
		game->player->y += game->player->dir_y * MOVE_SPEED;
	}
	else if (action == BACKWARD && is_move_possible(game, BACKWARD))
	{
		game->player->x -= game->player->dir_x * MOVE_SPEED;
		game->player->y -= game->player->dir_y * MOVE_SPEED;
	}
	else if (action == LEFT && is_move_possible(game, LEFT))
	{
		game->player->x += game->player->dir_y * MOVE_SPEED;
		game->player->y -= game->player->dir_x * MOVE_SPEED;
	}
	else if (action == RIGHT && is_move_possible(game, RIGHT))
	{
		game->player->x -= game->player->dir_y * MOVE_SPEED;
		game->player->y += game->player->dir_x * MOVE_SPEED;
	}
	update_map(game);
}

void	rotate_player(t_game *game, t_action action)
{
	if (action == TURN_LEFT)
		game->player->rotation -= (180 / PI) * ROTATION_SPEED;
	else if (action == TURN_RIGHT)
		game->player->rotation += (180 / PI) * ROTATION_SPEED;
	game->player->dir_x = cos(game->player->rotation);
	game->player->dir_y = sin(game->player->rotation);
	update_map(game);
}
