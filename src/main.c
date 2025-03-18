/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:43:29 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/17 14:32:18 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	print_ascii_art();
	if (parsing(ac, av) == ERROR)
		return (EXIT_FAILURE);
	msg("Map file has been analyzed and is complete/valid", TRUE, FALSE, 0);
	game = init(av[1]);
	if (!game)
		return (msg("Error while initializing the game", TRUE, TRUE, 1));
	start_game(game);
	return (msg("Exit...", TRUE, FALSE, EXIT_SUCCESS));
}
