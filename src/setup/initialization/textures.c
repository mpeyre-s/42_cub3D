/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:58:48 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/20 15:14:53 by mathispeyre      ###   ########.fr       */
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
