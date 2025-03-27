/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:26:26 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/27 15:14:49 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	calculate_move(t_game *game, t_action action)
{
	if (action == FOWARD)
	{
		game->player->x += game->player->dir_x * MOVE_SPEED;
		game->player->y += game->player->dir_y * MOVE_SPEED;
	}
	else if (action == BACKWARD)
	{
		game->player->x -= game->player->dir_x * (MOVE_SPEED / 2);
		game->player->y -= game->player->dir_y * (MOVE_SPEED / 2);
	}
	else if (action == LEFT)
	{
		game->player->x += game->player->dir_y * MOVE_SPEED;
		game->player->y -= game->player->dir_x * MOVE_SPEED;
	}
	else if (action == RIGHT)
	{
		game->player->x -= game->player->dir_y * MOVE_SPEED;
		game->player->y += game->player->dir_x * MOVE_SPEED;
	}
	return (TRUE);
}

int	is_move_possible(t_game *game, double x, double y)
{
	if (game->map->grid[(int)floor(y)][(int)floor(x)] == 1)
		return (FALSE);
	return (TRUE);
}

void	move_player(t_game *game, t_action action)
{
	double	old_x;
	double	old_y;

	old_x = game->player->x;
	old_y = game->player->y;
	calculate_move(game, action);
	if (!is_move_possible(game, game->player->x, old_y))
		game->player->x = old_x;
	if (!is_move_possible(game, old_x, game->player->y))
		game->player->y = old_y;
	update_map(game);
}

void	rotate_player(t_game *game, t_action action)
{
	if (action == TURN_LEFT)
		game->player->rotation -= ROTATION_SPEED;
	else if (action == TURN_RIGHT)
		game->player->rotation += ROTATION_SPEED;
	if (game->player->rotation < 0)
		game->player->rotation += 2 * M_PI;
	else if (game->player->rotation >= 2 * M_PI)
		game->player->rotation -= 2 * M_PI;
	game->player->dir_x = cos(game->player->rotation);
	game->player->dir_y = sin(game->player->rotation);
	game->player->plane_x = -sin(game->player->rotation) * FOV_SCALE;
	game->player->plane_y = cos(game->player->rotation) * FOV_SCALE;
	update_map(game);
}

