/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:12 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/28 08:35:11 by mathispeyre      ###   ########.fr       */
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
	mlx->frames = 1;
	return (mlx);
}

t_player	*init_player(t_init *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player) * 1);
	if (!player)
		return (NULL);
	player->x = data->x;
	player->y = data->y;
	player->rotation = data->rotation;
	player->direction = data->side;
	player->inventory = PICKAXE;
	init_player_direction(player);
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

// void	print_tdata(t_init *data)
// {
// 	if (!data)
// 	{
// 		printf("t_init structure is NULL\n");
// 		return;
// 	}
// 	printf("t_init structure:\n");
// 	printf("  Floor RGB: (%d, %d, %d)\n", data->floor->red, data->floor->green, data->floor->blue);
// 	printf("  Ceiling RGB: (%d, %d, %d)\n", data->ceiling->red, data->ceiling->green, data->ceiling->blue);
// 	printf("  South Texture: %s\n", data->south_texture);
// 	printf("  North Texture: %s\n", data->north_texture);
// 	printf("  East Texture: %s\n", data->east_texture);
// 	printf("  West Texture: %s\n", data->west_texture);
// 	printf("  Map Grid:\n");
// 	for (int i = 0; data->grid[i]; i++)
// 		printf("    %s\n", data->grid[i]);
// 	printf("  Map Width: %d\n", data->width);
// 	printf("  Map Height: %d\n", data->height);
// 	printf("  Player X: %.2f\n", data->x);
// 	printf("  Player Y: %.2f\n", data->y);
// 	printf("  Player Direction X: %.2f\n", data->dir_x);
// 	printf("  Player Direction Y: %.2f\n", data->dir_y);
// 	printf("  Player Rotation: %.2f\n", data->rotation);
// }

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
	game->player = init_player(data);
	game->keys = init_keys();
	free_init(data);
	return (game);
}
