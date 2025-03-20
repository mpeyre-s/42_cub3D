/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:51:42 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/20 16:33:45 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

char	**get_map_grid(char **file)
{
	size_t  i;
	size_t  j;
	size_t  tab_len;
	size_t  map_height;
	char    **map_grid;

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
