/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:12 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/07 17:05:27 by mathispeyre      ###   ########.fr       */
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
	return (mlx);
}

t_map	*init_map(char *map_path)
{
	t_map	*map;

	(void)map_path;
	map = malloc(sizeof(t_map) * 1);
	if (!map)
		return (NULL);
	map->width = 19;
	map->height = 10;
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

	int i = 0;
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
	for (int j = 0; j < map->width; j++)
		map->grid[0][j] = 1;

	map->grid[1][0] = 1;
	map->grid[1][1] = 0;
	map->grid[1][2] = 1;
	map->grid[1][3] = 0;
	map->grid[1][4] = 0;
	map->grid[1][5] = 1;
	map->grid[1][6] = 0;
	map->grid[1][7] = 0;
	map->grid[1][8] = 1;
	map->grid[1][9] = 0;
	map->grid[1][10] = 0;
	map->grid[1][11] = 1;
	map->grid[1][12] = 0;
	map->grid[1][13] = 0;
	map->grid[1][14] = 0;
	map->grid[1][15] = 0;
	map->grid[1][16] = 0;
	map->grid[1][17] = 0;
	map->grid[1][18] = 1;

	// Row 2
	map->grid[2][0] = 1;
	map->grid[2][1] = 0;
	map->grid[2][2] = 1;
	map->grid[2][3] = 1;
	map->grid[2][4] = 0;
	map->grid[2][5] = 0;
	map->grid[2][6] = 0;
	map->grid[2][7] = 0;
	map->grid[2][8] = 0;
	map->grid[2][9] = 1;
	map->grid[2][10] = 0;
	map->grid[2][11] = 0;
	map->grid[2][12] = 0;
	map->grid[2][13] = 0;
	map->grid[2][14] = 0;
	map->grid[2][15] = 1;
	map->grid[2][16] = 0;
	map->grid[2][17] = 0;
	map->grid[2][18] = 1;

	// Row 3
	map->grid[3][0] = 1;
	map->grid[3][1] = 0;
	map->grid[3][2] = 0;
	map->grid[3][3] = 1;
	map->grid[3][4] = 0;
	map->grid[3][5] = 0;
	map->grid[3][6] = 1;
	map->grid[3][7] = 0;
	map->grid[3][8] = 0;
	map->grid[3][9] = 1;
	map->grid[3][10] = 1;
	map->grid[3][11] = 1;
	map->grid[3][12] = 1;
	map->grid[3][13] = 1;
	map->grid[3][14] = 0;
	map->grid[3][15] = 1;
	map->grid[3][16] = 1;
	map->grid[3][17] = 1;
	map->grid[3][18] = 1;

	// Row 4
	map->grid[4][0] = 1;
	map->grid[4][1] = 0;
	map->grid[4][2] = 0;
	map->grid[4][3] = 1;
	map->grid[4][4] = 1;
	map->grid[4][5] = 1;
	map->grid[4][6] = 1;
	map->grid[4][7] = 0;
	map->grid[4][8] = 0;
	map->grid[4][9] = 0;
	map->grid[4][10] = 0;
	map->grid[4][11] = 0;
	map->grid[4][12] = 1;
	map->grid[4][13] = 0;
	map->grid[4][14] = 0;
	map->grid[4][15] = 1;
	map->grid[4][16] = 0;
	map->grid[4][17] = 0;
	map->grid[4][18] = 1;

	// Row 5
	map->grid[5][0] = 1;
	map->grid[5][1] = 0;
	map->grid[5][2] = 0;
	map->grid[5][3] = 0;
	map->grid[5][4] = 0;
	map->grid[5][5] = 0;
	map->grid[5][6] = 0;
	map->grid[5][7] = 0;
	map->grid[5][8] = 0;
	map->grid[5][9] = 0;
	map->grid[5][10] = 0;
	map->grid[5][11] = 0;
	map->grid[5][12] = 0;
	map->grid[5][13] = 0;
	map->grid[5][14] = 0;
	map->grid[5][15] = 1;
	map->grid[5][16] = 0;
	map->grid[5][17] = 0;
	map->grid[5][18] = 1;

	// Row 6
	map->grid[6][0] = 1;
	map->grid[6][1] = 0;
	map->grid[6][2] = 0;
	map->grid[6][3] = 1;
	map->grid[6][4] = 1;
	map->grid[6][5] = 1;
	map->grid[6][6] = 1;
	map->grid[6][7] = 1;
	map->grid[6][8] = 1;
	map->grid[6][9] = 1;
	map->grid[6][10] = 1;
	map->grid[6][11] = 1;
	map->grid[6][12] = 1;
	map->grid[6][13] = 0;
	map->grid[6][14] = 0;
	map->grid[6][15] = 1;
	map->grid[6][16] = 0;
	map->grid[6][17] = 0;
	map->grid[6][18] = 1;

	// Row 7
	map->grid[7][0] = 1;
	map->grid[7][1] = 1;
	map->grid[7][2] = 1;
	map->grid[7][3] = 1;
	map->grid[7][4] = 0;
	map->grid[7][5] = 0;
	map->grid[7][6] = 0;
	map->grid[7][7] = 0;
	map->grid[7][8] = 0;
	map->grid[7][9] = 0;
	map->grid[7][10] = 0;
	map->grid[7][11] = 0;
	map->grid[7][12] = 0;
	map->grid[7][13] = 0;
	map->grid[7][14] = 0;
	map->grid[7][15] = 1;
	map->grid[7][16] = 0;
	map->grid[7][17] = 1;
	map->grid[7][18] = 1;

	// Row 8
	map->grid[8][0] = 1;
	map->grid[8][1] = 0;
	map->grid[8][2] = 0;
	map->grid[8][3] = 0;
	map->grid[8][4] = 0;
	map->grid[8][5] = 0;
	map->grid[8][6] = 0;
	map->grid[8][7] = 0;
	map->grid[8][8] = 0;
	map->grid[8][9] = 1;
	map->grid[8][10] = 0;
	map->grid[8][11] = 0;
	map->grid[8][12] = 0;
	map->grid[8][13] = 0;
	map->grid[8][14] = 0;
	map->grid[8][15] = 0;
	map->grid[8][16] = 0;
	map->grid[8][17] = 0;
	map->grid[8][18] = 1;

	// Row 9
	for (int j = 0; j < map->width; j++)
		map->grid[9][j] = 1;

	return (map);
}

t_game	*init(char *map_path)
{
	t_game	*game;

	game = malloc(sizeof(t_game) * 1);
	if (!game)
		return (NULL);
	game->mlx = init_mlx();
	game->map = init_map(map_path);
	if (!game->mlx || !game->map)
		return (NULL);
	return (game);
}
