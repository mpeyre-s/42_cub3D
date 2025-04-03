/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:09:12 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/27 15:11:04 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*extract_map_line(char *start, char **next)
{
	char	*end;
	char	*temp;
	char	*c;
	int		k;

	end = start;
	while (*end && *end != '\n')
		end++;
	temp = malloc(end - start + 1);
	k = 0;
	c = start;
	while (c < end)
	{
		if (ft_isspace(*c))
			temp[k++] = '1';
		else
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

static char	*extract_config_line(char *start, char **next)
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

static void	pad_map_line(char **result, int i, size_t max_width)
{
	char	*temp;
	size_t	current_len;

	temp = result[i];
	result[i] = malloc(max_width + 1);
	if (!result[i])
		return ;
	ft_strcpy(result[i], temp);
	current_len = ft_strlen(temp);
	while (current_len < max_width)
		result[i][current_len++] = '1';
	result[i][current_len] = '\0';
	free(temp);
}

void	normalize_map_width(char **result, int j)
{
	size_t	max_width;
	int		i;

	max_width = 0;
	i = 6;
	while (i < j)
	{
		if (ft_strlen(result[i]) > max_width)
			max_width = ft_strlen(result[i]);
		i++;
	}
	i = 6;
	while (i < j)
	{
		if (ft_strlen(result[i]) < max_width)
			pad_map_line(result, i, max_width);
		i++;
	}
}

int	process_line(char **result, char **line, int j)
{
	char	*temp;

	if (j < 6)
		temp = extract_config_line(*line, line);
	else
		temp = extract_map_line(*line, line);
	if (!temp)
		return (-1);
	if (ft_strlen(temp) > 0)
	{
		result[j] = ft_strdup(temp);
		if (!result[j])
		{
			free(temp);
			return (-1);
		}
		j++;
	}
	free(temp);
	return (j);
}
