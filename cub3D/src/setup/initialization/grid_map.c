/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeyre-s <mpeyre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:51:42 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/04 17:34:25 by mpeyre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

char	**get_map_grid(char **file)
{
	size_t	i;
	size_t	j;
	size_t	tab_len;
	size_t	map_height;
	char	**map_grid;

	i = 0;
	tab_len = tab_of_tab_len(file);
	while (i < tab_len && file[i][0] != '1')
		i++;
	if (i == tab_len)
		return (NULL);
	map_height = tab_len - i;
	map_grid = malloc(sizeof(char *) * (map_height + 1));
	if (!map_grid)
		return (NULL);
	j = 0;
	while (i < tab_len)
	{
		map_grid[j] = ft_strdup(file[i]);
		i++;
		j++;
	}
	map_grid[j] = NULL;
	return (map_grid);
}

int	get_map_width(char **file)
{
	size_t	i;
	size_t	tab_len;

	i = 0;
	tab_len = tab_of_tab_len(file);
	while (file[i][0] != '1')
		i++;
	if (i == tab_len)
		return (0);
	return (ft_strlen(file[i]));
}

int	get_map_height(char **file)
{
	size_t	i;
	size_t	tab_len;

	i = 0;
	tab_len = tab_of_tab_len(file);
	while (file[i][0] != '1')
		i++;
	if (i == tab_len)
		return (0);
	return ((int)tab_len - i);
}

int	**init_grid(t_init *data, int width, int height)
{
	int	**grid;
	int	i;
	int	j;

	grid = malloc(sizeof(int *) * (height + 1));
	if (!grid)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		grid[i] = malloc(sizeof(int) * width);
		if (!grid[i])
			return (NULL);
		j = 0;
		while (j < width)
		{
			if (data->grid[i][j] - '0' == 1)
				grid[i][j] = 1;
			else
				grid[i][j] = 0;
			j++;
		}
	}
	data->grid[i] = NULL;
	return (grid);
}
