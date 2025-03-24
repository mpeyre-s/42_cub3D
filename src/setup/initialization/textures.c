/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:58:48 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/24 12:33:12 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

char	*get_south_texture(char **file)
{
	size_t	i;

	i = 0;
	while (i < 7 && ft_strncmp(file[i], "SO", 2) != 0)
		i++;
	if (i == 6)
		return (NULL);
	return (ft_substr(file[i], 2, ft_strlen(file[i]) - 2));
}

char	*get_north_texture(char **file)
{
	size_t	i;

	i = 0;
	while (i < 7 && ft_strncmp(file[i], "NO", 2) != 0)
		i++;
	if (i == 6)
		return (NULL);
	return (ft_substr(file[i], 2, ft_strlen(file[i]) - 2));
}

char	*get_east_texture(char **file)
{
	size_t	i;

	i = 0;
	while (i < 7 && ft_strncmp(file[i], "EA", 2) != 0)
		i++;
	if (i == 6)
		return (NULL);
	return (ft_substr(file[i], 2, ft_strlen(file[i]) - 2));
}

char	*get_west_texture(char **file)
{
	size_t	i;

	i = 0;
	while (i < 7 && ft_strncmp(file[i], "WE", 2) != 0)
		i++;
	if (i == 6)
		return (NULL);
	return (ft_substr(file[i], 2, ft_strlen(file[i]) - 2));
}

void	init_textures(t_map *map, t_game *game)
{
	map->north.img = mlx_xpm_file_to_image(game->mlx->mlx, map->NO_path, &map->north.width, &map->north.height);
	map->south.img = mlx_xpm_file_to_image(game->mlx->mlx, map->SO_path, &map->south.width, &map->south.height);
	map->east.img = mlx_xpm_file_to_image(game->mlx->mlx, map->EA_path, &map->east.width, &map->east.height);
	map->west.img = mlx_xpm_file_to_image(game->mlx->mlx, map->WE_path, &map->west.width, &map->west.height);
	if (!map->north.img || !map->south.img || !map->east.img || !map->west.img)
	{
		printf("Erreur : Impossible de charger l'une des textures.\n");
		exit(1);
	}
	map->north.addr = mlx_get_data_addr(map->north.img, &map->north.bpp, &map->north.line_length, &map->north.endian);
	map->south.addr = mlx_get_data_addr(map->south.img, &map->south.bpp, &map->south.line_length, &map->south.endian);
	map->east.addr = mlx_get_data_addr(map->east.img, &map->east.bpp, &map->east.line_length, &map->east.endian);
	map->west.addr = mlx_get_data_addr(map->west.img, &map->west.bpp, &map->west.line_length, &map->west.endian);
}
