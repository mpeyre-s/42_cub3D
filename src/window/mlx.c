/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:20:52 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/12 00:22:55 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_mlx(t_game *game)
{
	print_keycode_config(game);
	mlx_hook(game->mlx->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L<<1, key_release, game);
	mlx_loop_hook(game->mlx->mlx, loop_hook, game);
	mlx_hook(game->mlx->win, 17, 1L << 17, close_hook, game);
	msg("Game started...", TRUE, FALSE, 0);
	return (SUCCES);
}

// int	start_mlx(t_game *game)
// {
// 	game->mlx->mlx = mlx_init();
// 	if (!game->mlx->mlx)
// 	{
// 		printf("Error: mlx_init() failed\n");
// 		return (ERROR);
// 	}

// 	game->mlx->win = mlx_new_window(game->mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
// 	if (!game->mlx->win)
// 	{
// 		printf("Error: mlx_new_window() failed\n");
// 		return (ERROR);
// 	}

// 	game->mlx->img = mlx_new_image(game->mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	if (!game->mlx->img)
// 	{
// 		printf("Error: mlx_new_image() failed\n");
// 		return (ERROR);
// 	}

// 	game->mlx->addr = mlx_get_data_addr(game->mlx->img, &game->mlx->bits_per_pixel,
// 		&game->mlx->line_length, &game->mlx->endian);
// 	if (!game->mlx->addr)
// 	{
// 		printf("Error: mlx_get_data_addr() failed\n");
// 		return (ERROR);
// 	}

// 	// Ajoute un print pour confirmer que tout est bon
// 	printf("MLX initialized successfully!\n");

// 	// Gestion des touches et fermeture
// 	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
// 	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
// 	mlx_hook(game->mlx->win, 17, 1L << 17, close_hook, game);

// 	// Boucle principale
// 	mlx_loop_hook(game->mlx->mlx, loop_hook, game);

// 	msg("Game started...", TRUE, FALSE, 0);
// 	return (SUCCES);
// }



int	destroy_mlx(t_game *game)
{
	if (game->mlx->img)
		mlx_destroy_image(game->mlx->mlx, game->mlx->img);
	if (game->mlx->win)
		mlx_destroy_window(game->mlx->mlx, game->mlx->win);
	// if (game->mlx->os == LINUX)
	// {
	// 	if (game->mlx->mlx)
	// 	{
	// 		mlx_destroy_display(game->mlx->mlx);
	// 		free(game->mlx->mlx);
	// 	}
	// }
	return (SUCCES);
}

