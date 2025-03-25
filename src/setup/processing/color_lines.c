/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:22:02 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/25 15:34:36 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

static int	coma_count(char *line)
{
	int		coma_count;
	size_t	i;

	coma_count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == ',')
			coma_count++;
	}
	return (coma_count);
}

static int	check_line(char *line)
{
	int	i;
	int	count;

	if (!line || ft_strlen(line) < 6 || coma_count(line) != 2)
		return (ERROR);
	i = 1;
	count = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			while (ft_isdigit(line[i]))
				i++;
			count++;
		}
		else if (line[i] == ',')
			i++;
		else
			return (ERROR);
	}
	if (count == 3)
		return (SUCCES);
	return (ERROR);
}

int	process_color_lines(char **file)
{
	int	c_flag;
	int	f_flag;

	c_flag = 0;
	f_flag = 0;
	if (check_line(file[0]) == ERROR)
		return (msg("Map file 1st color line, check ID (C/F) + RGB",
			TRUE, TRUE, ERROR));
	if (check_line(file[1]) == ERROR)
		return (msg("Map file 2nd color line, check ID (C/F) + RGB",
			TRUE, TRUE, ERROR));
	if (file[0][0] == 'F')
		f_flag++;
	if (file[1][0] == 'F')
		f_flag++;
	if (file[0][0] == 'C')
		c_flag++;
	if (file[1][0] == 'C')
		c_flag++;
	if (c_flag == 1 && f_flag == 1)
		return (SUCCES);
	msg("Map file, Invalid textures IDs, must be only 'C' & 'F'",
		TRUE, TRUE, ERROR);
	return (ERROR);
}

void	init_color(t_map *map)
{
	map->floor_color = (map->floor->red << 16) | (map->floor->green << 8) | (map->floor->blue);
	map->sky_color = (map->ceiling->red << 16) | (map->ceiling->green << 8) | (map->ceiling->blue);

}

