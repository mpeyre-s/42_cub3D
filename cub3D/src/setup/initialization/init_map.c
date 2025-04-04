/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeyre-s <mpeyre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:32:53 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/04 15:08:40 by mpeyre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

static t_map	*allocate_map(t_init *data)
{
	t_map	*map;

	map = malloc(sizeof(t_map) * 1);
	if (!map)
		return (NULL);
	map->width = data->width;
	map->height = data->height;
	map->cell_width = CELL_LENGTH;
	map->cell_height = CELL_LENGTH;
	map->px_width = map->width * map->cell_width;
	map->px_height = map->height * map->cell_height;
	map->ceiling = malloc(sizeof(t_rgb));
	if (!map->ceiling)
		return (NULL);
	map->floor = malloc(sizeof(t_rgb));
	if (!map->floor)
	{
		free(map->ceiling);
		return (NULL);
	}
	return (map);
}

static void	fill_map_data(t_map *map, t_init *data)
{
	map->ceiling->red = data->ceiling->red;
	map->ceiling->green = data->ceiling->green;
	map->ceiling->blue = data->ceiling->blue;
	map->floor->red = data->floor->red;
	map->floor->green = data->floor->green;
	map->floor->blue = data->floor->blue;
	map->no_path = ft_strdup(data->north_texture);
	map->so_path = ft_strdup(data->south_texture);
	map->we_path = ft_strdup(data->west_texture);
	map->ea_path = ft_strdup(data->east_texture);
	map->grid = init_grid(data, map->width, map->height);
}

static void	reinforce_walls(int **grid, int height, int width)
{
	size_t	i;
	size_t	j;
	size_t	max_width;
	size_t	max_height;

	i = 0;
	max_height = height - 1;
	max_width = width - 1;
	while (i <= max_height)
	{
		j = 0;
		while (j <= max_width)
		{
			if (i == 0 || i == max_height || j == 0 || j == max_width)
				grid[i][j] = 2;
			j++;
		}
		i++;
	}
}

t_map	*init_map(t_init *data)
{
	t_map	*map;

	map = allocate_map(data);
	if (!map)
		return (NULL);
	fill_map_data(map, data);
	if (!map->grid)
	{
		free(map->ceiling);
		free(map->floor);
		free(map->no_path);
		free(map->so_path);
		free(map->we_path);
		free(map->ea_path);
		free(map);
		return (NULL);
	}
	reinforce_walls(map->grid, map->height, map->width);
	return (map);
}
