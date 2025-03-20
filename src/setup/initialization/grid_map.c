/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:51:42 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/20 15:29:38 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

char	**get_map_grid(char **file)
{
	size_t	i;
	size_t	j;
	size_t	tab_len;
	char	**map_grid;

	i = 0;
	tab_len = tab_of_tab_len(file);
	while (file[i][0] != '1')
		i++;
	if (i == tab_len)
		return (NULL);
	map_grid = malloc(sizeof(char *) * (tab_len - i));
	if (!map_grid)
		return (NULL);
	j = -1;
	while (i < tab_len)
	{
		map_grid[++j] = ft_strdup(file[i]);
		i++;
	}
	return (map_grid);
}
