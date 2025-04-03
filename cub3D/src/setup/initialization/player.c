/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:03:48 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/01 16:41:46 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

double	get_x_pos(char **file)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] == 'S' || file[i][j] == 'N'
				|| file[i][j] == 'W' || file[i][j] == 'E')
				return ((double)j + 0.5);
		}
	}
	return (0);
}

double	get_y_pos(char **file)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] == 'S' || file[i][j] == 'N'
				|| file[i][j] == 'W' || file[i][j] == 'E')
				return ((double)i + 0.5);
		}
	}
	return (0);
}

double	get_rotation(char **file)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] == 'N')
				return (3 * PI / 2);
			else if (file[i][j] == 'S')
				return (PI / 2);
			else if (file[i][j] == 'E')
				return (0.0);
			else if (file[i][j] == 'W')
				return (PI);
		}
	}
	return (0.0);
}

char	get_player_side(char **file)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] == 'N')
				return ('N');
			else if (file[i][j] == 'S')
				return ('S');
			else if (file[i][j] == 'E')
				return ('E');
			else if (file[i][j] == 'W')
				return ('W');
		}
	}
	return ('z');
}
