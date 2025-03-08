/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:24 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/08 19:22:29 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_hook(int keycode, t_game *game)
{
	if (game->mlx->os == LINUX)
	{
		if (keycode == LIN_ESC_KEY)
			exit_program(game);
	}
	else if (game->mlx->os == MACOS)
	{
		if (keycode == MAC_ESC_KEY)
			exit_program(game);
	}
	return (SUCCES);
}

int	close_hook(t_game *game)
{
	exit_program(game);
	return (SUCCES);
}
