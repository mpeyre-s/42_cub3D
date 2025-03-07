/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:17 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/07 16:54:54 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_map_valid(char *map_path)
{
	if (!map_path)
		return (FALSE);
	return (TRUE);
}

int	parsing(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (msg(STR_PARSE1, TRUE, TRUE, ERROR));
	if (is_map_valid(av[1]) == FALSE)
		return (msg(STR_PARSE2, TRUE, TRUE, ERROR));
	return (SUCCES);
}
