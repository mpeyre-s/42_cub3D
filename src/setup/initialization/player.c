/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:03:48 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/20 17:27:39 by mathispeyre      ###   ########.fr       */
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

double	get_dirx(char **file)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] == 'E')
				return (1.0);
			else if (file[i][j] == 'W')
				return (-1.0);
			else if (file[i][j] == 'N' || file[i][j] == 'S')
				return (0.0);
		}
	}
	return (0.0);
}

double	get_diry(char **file)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] == 'S')
				return (1.0);
			else if (file[i][j] == 'N')
				return (-1.0);
			else if (file[i][j] == 'E' || file[i][j] == 'W')
				return (0.0);
		}
	}
	return (0.0);
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
