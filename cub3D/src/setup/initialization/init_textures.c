/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:39:08 by spike             #+#    #+#             */
/*   Updated: 2025/04/03 20:25:50 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	init_addr(t_game *game, t_map *map)
{
	(void)game;
	map->north.addr = mlx_get_data_addr(map->north.img,
			&map->north.bpp, &map->north.line_length, &map->north.endian);
	map->south.addr = mlx_get_data_addr(map->south.img,
			&map->south.bpp, &map->south.line_length, &map->south.endian);
	map->east.addr = mlx_get_data_addr(map->east.img,
			&map->east.bpp, &map->east.line_length, &map->east.endian);
	map->west.addr = mlx_get_data_addr(map->west.img,
			&map->west.bpp, &map->west.line_length, &map->west.endian);
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
	if (!map->north.img || !map->south.img
		|| !map->east.img || !map->west.img)
		exit(1);
	init_addr(game, map);
}
