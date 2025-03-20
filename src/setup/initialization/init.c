/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:12 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/20 16:45:00 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx) * 1);
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
	mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx->os = detect_os();
	return (mlx);
}

t_map	*init_map(t_init *data)
{
	t_map	*map;

	map = malloc(sizeof(t_map) * 1);
	if (!map)
		return (NULL);
	map->width = data->width;
	map->height = data->height;
	map->cell_width = CELL_LENGTH;
	map->cell_height = CELL_LENGTH;
	map->px_width = map->width * map->cell_width;
	map->px_height = map->height * map->cell_height;
	map->ceiling = data->ceiling;
	map->floor = data->floor;
	map->NO_path = ft_strdup(data->north_texture);
	map->SO_path = ft_strdup(data->south_texture);
	map->WE_path = ft_strdup(data->west_texture);
	map->EA_path = ft_strdup(data->east_texture);
	map->grid = init_grid(data, map->width, map->height);
	if (!map->grid)
		return (NULL);
	return (map);
}

t_player	*init_player(int map_width, int map_height)
{
	t_player	*player;

	player = malloc(sizeof(t_player) * 1);
	if (!player)
		return (NULL);
	player->x = map_width / 2;
	player->y = map_height / 2;
	player->rotation = 0;
	player->dir_x = 1.0;
	player->dir_y = 0.0;
	return (player);
}

t_keys	*init_keys(void)
{
	t_keys	*keys;

	keys = malloc(sizeof(t_keys) * 1);
	if (!keys)
		return (NULL);
	keys->forward = 0;
	keys->backward = 0;
	keys->left = 0;
	keys->right = 0;
	keys->rotate_left = 0;
	keys->rotate_right = 0;
	return (keys);
}

t_game	*init(char *map_path)
{
	t_game	*game;
	t_init	*data;

	msg("Program initialization has started", TRUE, FALSE, SUCCES);
	game = malloc(sizeof(t_game) * 1);
	data = NULL;
	if (!game)
		return (NULL);
	data = init_data(map_path);
	game->mlx = init_mlx();
	game->map = init_map(data);
	game->player = init_player(game->map->width, game->map->height);
	game->keys = init_keys();
	free_init(data);
	return (game);
}
