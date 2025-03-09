/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:12 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/09 19:41:09 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_os	detect_os(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	fd = open("/etc/os-release", O_RDONLY);
	if (fd == -1)
	{
		msg("Non-linux environment detected, assuming macOS", TRUE, FALSE, 0);
		return (MACOS);
	}
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (strstr(buffer, "PRETTY_NAME")) {
			close(fd);
			msg("Linux environment detected", TRUE, FALSE, 0);
			return (LINUX);
		}
	}
	close(fd);
	msg("Unknown environment detected, assuming linux", TRUE, FALSE, 0);
	return (UNKNOWN);
}

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
	map->cell_width = WINDOW_WIDTH / map->width;
	map->cell_height = WINDOW_HEIGHT / map->height;
	if (map->cell_width > map->cell_height)
		map->cell_width = map->cell_height;
	else
		map->cell_height = map->cell_width;
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
	for (i = 0; i < map->height; i++)
		for (int j = 0; j < map->width; j++)
			map->grid[i][j] = grid_values[i][j];
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
	if (!game->mlx || !game->map || !game->player)
		return (NULL);
	return (game);
}
