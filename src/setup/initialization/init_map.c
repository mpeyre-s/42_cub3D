/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:32:53 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/24 13:33:58 by mathispeyre      ###   ########.fr       */
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
	map->NO_path = ft_strdup(data->north_texture);
	map->SO_path = ft_strdup(data->south_texture);
	map->WE_path = ft_strdup(data->west_texture);
	map->EA_path = ft_strdup(data->east_texture);
	map->grid = init_grid(data, map->width, map->height);
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
		free(map->NO_path);
		free(map->SO_path);
		free(map->WE_path);
		free(map->EA_path);
		free(map);
		return (NULL);
	}
	return (map);
}
