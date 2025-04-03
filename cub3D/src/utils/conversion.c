/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:08:14 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/02 16:16:03 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	count_lines(char *content)
{
	int		line_count;
	char	*line;

	line_count = 0;
	line = content;
	while (*line)
	{
		if (*line == '\n')
		{
			if (!is_empty_line(line + 1))
				line_count++;
		}
		line++;
	}
	return (line_count + 1);
}

static void	free_result(char **result, int j)
{
	while (j > 0)
		free(result[--j]);
	free(result);
}

char	**convert_content(char *content)
{
	char	**result;
	char	*line;
	int		j;
	int		new_j;

	result = malloc(sizeof(char *) * (count_lines(content) + 1));
	if (!result)
		return (NULL);
	j = 0;
	line = content;
	while (*line)
	{
		new_j = process_line(result, &line, j);
		if (new_j == -1)
		{
			free_result(result, j);
			return (NULL);
		}
		j = new_j;
	}
	result[j] = NULL;
	normalize_map_width(result, j);
	return (result);
}

unsigned int	invert_color(unsigned int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = 255 - ((color >> 16) & 0xFF);
	g = 255 - ((color >> 8) & 0xFF);
	b = 255 - (color & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

int	get_steps_and_increments(int *start, int *end, int *inc)
{
	int	dx;
	int	dy;
	int	steps;

	dx = end[0] - start[0];
	dy = end[1] - start[1];
	steps = abs(dx);
	if (abs(dy) > steps)
		steps = abs(dy);
	inc[0] = (dx * 1000) / steps;
	inc[1] = (dy * 1000) / steps;
	return (steps);
}
