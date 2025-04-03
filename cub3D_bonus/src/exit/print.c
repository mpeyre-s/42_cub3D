/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:41:30 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/28 10:47:08 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	msg(char *msg, int endl, int is_error, int value)
{
	if (!msg)
		return (ERROR);
	printf("%s", RESET_COLOR);
	if (is_error == TRUE)
		printf("%sError : ", RED);
	printf("%s", msg);
	if (value != 0)
		printf(" (%d)", value);
	if (endl == TRUE)
		printf("\n");
	printf("%s", RESET_COLOR);
	return (value);
}

int	print_keycode_config(t_game *game)
{
	if (game->mlx->os == LINUX)
		msg("Configuring linux keycodes", TRUE, FALSE, 0);
	else if (game->mlx->os == MACOS)
		msg("Configuring macOS keycodes", TRUE, FALSE, 0);
	else if (game->mlx->os == UNKNOWN)
		msg("Configuring linux keycodes because of unknown OS", TRUE, FALSE, 0);
	return (SUCCES);
}

int	print_ascii_art(void)
{
	printf("%s", ASCII_L1);
	printf("%s", ASCII_L2);
	printf("%s", ASCII_L3);
	printf("%s", ASCII_L4);
	printf("%s", ASCII_L5);
	printf("%s", ASCII_L6);
	printf("%s", RESET_COLOR);
	return (738);
}

void	print_tab_of_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	print_tab_of_tab_int(int **tab, int rows, int cols)
{
	int	i;
	int	j;

	if (!tab)
		return ;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("%d ", tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
