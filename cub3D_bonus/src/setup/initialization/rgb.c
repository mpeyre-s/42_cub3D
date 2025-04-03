/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:52:21 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/02 14:36:08 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

int	get_pixel_from_texture(t_txt *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = (char *)texture->addr + (y * texture->line_length + x
			* (texture->bpp / 8));
	color = *(int *)pixel;
	return (color);
}

static int	fill_rgb_struct(t_rgb **rgb, char *line)
{
	char	**values;
	int		i;

	values = ft_split(line, ',');
	if (!values)
		return (ERROR);
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
		return (free_split(values), ERROR);
	(*rgb)->red = ft_atouint8(values[0]);
	(*rgb)->green = ft_atouint8(values[1]);
	(*rgb)->blue = ft_atouint8(values[2]);
	free_split(values);
	return (SUCCES);
}

t_rgb	*get_floor_rgb(char **file)
{
	size_t	i;
	t_rgb	*rgb;
	char	*line;

	i = 0;
	rgb = malloc(sizeof(t_rgb) * 1);
	if (!rgb)
		return (NULL);
	while (i < 7 && ft_strncmp(file[i], "F", 1) != 0)
		i++;
	if (i == 6)
	{
		rgb->red = 0;
		rgb->green = 0;
		rgb->blue = 0;
		return (rgb);
	}
	line = ft_substr(file[i], 1, ft_strlen(file[i]) - 1);
	if (fill_rgb_struct(&rgb, line) == ERROR)
		return (free(line), NULL);
	return (free(line), rgb);
}

t_rgb	*get_ceiling_rgb(char **file)
{
	size_t	i;
	t_rgb	*rgb;
	char	*line;

	i = 0;
	rgb = malloc(sizeof(t_rgb) * 1);
	if (!rgb)
		return (NULL);
	while (i < 7 && ft_strncmp(file[i], "C", 1) != 0)
		i++;
	if (i == 6)
	{
		rgb->red = 0;
		rgb->green = 0;
		rgb->blue = 0;
		return (rgb);
	}
	line = ft_substr(file[i], 1, ft_strlen(file[i]) - 1);
	if (fill_rgb_struct(&rgb, line) == ERROR)
		return (free(line), NULL);
	return (free(line), rgb);
}
