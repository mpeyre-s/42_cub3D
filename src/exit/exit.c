/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:39:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/24 12:19:10 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	free_map(t_game *game)
{
	int	i;

	if (game->map->NO_path)
		free(game->map->NO_path);
	if (game->map->SO_path)
		free(game->map->SO_path);
	if (game->map->WE_path)
		free(game->map->WE_path);
	if (game->map->EA_path)
		free(game->map->EA_path);
	if (game->map->floor)
		free(game->map->floor);
	if (game->map->ceiling)
		free(game->map->ceiling);
	if (game->map->grid)
	{
		i = 0;
		while (game->map->grid[i])
		{
			free(game->map->grid[i]);
			i++;
		}
		free(game->map->grid);
	}
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
