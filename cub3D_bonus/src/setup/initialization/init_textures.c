/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:39:08 by spike             #+#    #+#             */
/*   Updated: 2025/04/02 16:35:19 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	init_addr(t_game *game, t_map *map)
{
	map->north.addr = mlx_get_data_addr(map->north.img,
			&map->north.bpp, &map->north.line_length, &map->north.endian);
	map->south.addr = mlx_get_data_addr(map->south.img,
			&map->south.bpp, &map->south.line_length, &map->south.endian);
	map->east.addr = mlx_get_data_addr(map->east.img,
			&map->east.bpp, &map->east.line_length, &map->east.endian);
	map->west.addr = mlx_get_data_addr(map->west.img,
			&map->west.bpp, &map->west.line_length, &map->west.endian);
	map->floors.addr = mlx_get_data_addr(map->floors.img,
			&map->floors.bpp, &map->floors.line_length, &map->floors.endian);
	game->pickaxe_hud.addr = mlx_get_data_addr(game->pickaxe_hud.img,
			&game->pickaxe_hud.bpp, &game->pickaxe_hud.line_length,
			&game->pickaxe_hud.endian);
	game->block_hud.addr = mlx_get_data_addr(game->block_hud.img,
			&game->block_hud.bpp, &game->block_hud.line_length,
			&game->block_hud.endian);
}

void	init_textures(t_map *map, t_game *game)
{
	game->floor = malloc(sizeof(t_floor));
	map->north.img = mlx_xpm_file_to_image(game->mlx->mlx,
			map->no_path, &map->north.width, &map->north.height);
	map->south.img = mlx_xpm_file_to_image(game->mlx->mlx,
			map->so_path, &map->south.width, &map->south.height);
	map->east.img = mlx_xpm_file_to_image(game->mlx->mlx,
			map->ea_path, &map->east.width, &map->east.height);
	map->west.img = mlx_xpm_file_to_image(game->mlx->mlx,
			map->we_path, &map->west.width, &map->west.height);
	map->floors.img = mlx_xpm_file_to_image(game->mlx->mlx,
			"assets/textures/mossy.xpm", &map->floors.width,
			&map->floors.height);
	game->pickaxe_hud.img = mlx_xpm_file_to_image(game->mlx->mlx,
			"assets/textures/pickaxe_hud.xpm",
			&game->pickaxe_hud.width, &game->pickaxe_hud.height);
	game->block_hud.img = mlx_xpm_file_to_image(game->mlx->mlx,
			"assets/textures/block_hud.xpm",
			&game->block_hud.width, &game->block_hud.height);
	if (!map->north.img || !map->south.img
		|| !map->east.img || !map->west.img || !map->floors.img
		|| !game->block_hud.img || !game->block_hud.img)
		exit(1);
	init_addr(game, map);
}
