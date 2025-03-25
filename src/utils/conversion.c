/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:08:14 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/25 18:39:18 by mathispeyre      ###   ########.fr       */
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

static char	*extract_line(char *start, char **next)
{
	char	*end;
	char	*temp;
	char	*c;
	int		k;

	end = start;
	while (*end && *end != '\n')
		end++;
	temp = malloc(end - start + 1);
	if (!temp)
		return (NULL);
	k = 0;
	c = start;
	while (c < end)
	{
		if (!ft_isspace(*c))
			temp[k++] = *c;
		c++;
	}
	temp[k] = '\0';
	if (*end)
		*next = end + 1;
	else
		*next = end;
	return (temp);
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
	char	*temp;
	int		j;

	result = malloc(sizeof(char *) * (count_lines(content) + 1));
	if (!result)
		return (NULL);
	j = 0;
	line = content;
	while (*line)
	{
		temp = extract_line(line, &line);
		if (!temp || (ft_strlen(temp) > 0 &&
			!(result[j] = ft_strdup(temp))))
		{
			free_result(result, j);
			return (free(temp), NULL);
		}
		if (ft_strlen(temp) > 0)
			j++;
		free(temp);
	}
	result[j] = NULL;
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
