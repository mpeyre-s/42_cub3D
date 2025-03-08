/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:39:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/07 18:02:04 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	free_map(t_game *game)
{
	if (game->map->NO_path)
		free(game->map->NO_path);
	if (game->map->SO_path)
		free(game->map->SO_path);
	if (game->map->WE_path)
		free(game->map->WE_path);
	if (game->map->EA_path)
		free(game->map->EA_path);
	//here free grid
	free(game->map);
}

void	exit_program(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game);
	if (game->mlx)
	{
		destroy_mlx(game);
		free(game->mlx);
	}
	free(game);
}
