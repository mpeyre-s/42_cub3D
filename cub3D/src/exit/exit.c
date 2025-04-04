/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:39:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/04 13:36:44 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	free_map(t_game *game)
{
	int	i;

	if (game->map->no_path)
		free(game->map->no_path);
	if (game->map->so_path)
		free(game->map->so_path);
	if (game->map->we_path)
		free(game->map->we_path);
	if (game->map->ea_path)
		free(game->map->ea_path);
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

void	free_textures(t_map *map, t_game *game)
{
	if (map->north.img)
		mlx_destroy_image(game->mlx->mlx, map->north.img);
	if (map->south.img)
		mlx_destroy_image(game->mlx->mlx, map->south.img);
	if (map->east.img)
		mlx_destroy_image(game->mlx->mlx, map->east.img);
	if (map->west.img)
		mlx_destroy_image(game->mlx->mlx, map->west.img);
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
		free_textures(game->map, game);
		free(game->mlx);
	}
	free(game);
}
