/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:12 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/19 20:58:53 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

t_map	*init_map(char *map_path)
{
	t_map	*map;
	int		i;

	(void)map_path;
	map = malloc(sizeof(t_map) * 1);
	if (!map)
		return (NULL);
	map->width = 19;
	map->height = 10;
	map->cell_width = CELL_LENGTH;
	map->cell_height = CELL_LENGTH;
	map->px_width = map->width * map->cell_width;
	map->px_height = map->height * map->cell_height;
	map->ceiling_color[0] = 99;
	map->ceiling_color[1] = 99;
	map->ceiling_color[2] = 99;
	map->floor_color[0] = 76;
	map->floor_color[1] = 76;
	map->floor_color[2] = 76;
	map->NO_path = ft_strdup("./path_to_the_north_texture");
	map->SO_path = ft_strdup("./path_to_the_south_texture");
	map->WE_path = ft_strdup("./path_to_the_west_texture");
	map->EA_path = ft_strdup("./path_to_the_east_texture");
	map->grid = malloc(sizeof(int *) * map->height);
	if (!map->grid)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(sizeof(int) * map->width);
		if (!map->grid[i])
		{
			while (--i >= 0)
				free(map->grid[i]);
			free(map->grid);
			return (NULL);
		}
		i++;
	}
	int grid_values[10][19] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1},
		{1,0,1,0,1,1,1,1,0,1,0,0,0,0,0,1,0,0,1},
		{1,0,1,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1},
		{1,0,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,1,1,1,0,1,1,1,1,1,0,1,0,0,1,0,0,1},
		{1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1},
		{1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	// int grid_values[20][19] = {
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	//  };
	for (i = 0; i < map->height; i++)
		for (int j = 0; j < map->width; j++)
			map->grid[i][j] = grid_values[i][j];
	return (map);
}

t_player	*init_player(int map_width, int map_height)
{
	t_player	*player;
	(void)map_height;
	(void)map_width;
	player = malloc(sizeof(t_player) * 1);
	if (!player)
		return (NULL);
	player->x = 2;
	player->y = 2;
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

	msg("Program initialization has started", TRUE, FALSE, SUCCES);
	game = malloc(sizeof(t_game) * 1);
	if (!game)
		return (NULL);
	game->mlx = init_mlx();
	game->map = init_map(map_path);
	game->player = init_player(game->map->width, game->map->height);
	game->keys = init_keys();
	if (!game->mlx || !game->map || !game->player || !game->keys)
		return (NULL);
	return (game);
}
