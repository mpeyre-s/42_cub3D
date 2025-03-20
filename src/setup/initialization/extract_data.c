/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:31:20 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/20 16:32:12 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

size_t	tab_of_tab_len(char **tab)
{
	size_t	len;

	len = 0;
	if (!tab)
		return (len);
	while (tab[len])
		len++;
	return (len);
}

static char	**process_extraction(char *path)
{
	char	*file_inline;
	char	**file;

	file_inline = read_file(path);
	if (!file_inline)
		return (NULL);
	file = convert_content(file_inline);
	if (!file)
		return (free(file_inline), NULL);
	return (free(file_inline), file);
}

static int	data_checkup(t_init	*data)
{
	if (!data->floor || !data->ceiling || !data->south_texture
		|| !data->north_texture || !data->east_texture
		|| !data->west_texture || !data->grid)
		return (msg("Data checkup", TRUE, TRUE, ERROR));
	return (SUCCES);
}

int	free_init(t_init *data)
{
	if (!data)
		return (ERROR);
	if (data->floor)
		free(data->floor);
	if (data->ceiling)
		free(data->ceiling);
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->east_texture)
		free(data->east_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->grid)
		free_split(data->grid);
	free(data);
	return (SUCCES);
}

t_init	*init_data(char *path)
{
	t_init	*data;
	char	**file;

	data = malloc(sizeof(t_init) * 1);
	if (!data)
		return (NULL);
	file = process_extraction(path);
	data->floor = get_floor_rgb(file);
	data->ceiling = get_ceiling_rgb(file);
	data->south_texture = get_south_texture(file);
	data->north_texture = get_north_texture(file);
	data->east_texture = get_east_texture(file);
	data->west_texture = get_west_texture(file);
	data->grid = get_map_grid(file);
	data->width = get_map_width(file);
	data->height = get_map_height(file);
	if (data_checkup(data) == ERROR)
		return (free_init(data), free_split(file), NULL);
	return (free_split(file), data);
}
