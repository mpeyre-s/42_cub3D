/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:02:28 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/19 10:46:11 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

int	check_file_when_colors_first(char **file, size_t len)
{
	if (process_color_lines(file) == ERROR)
		return (ERROR);
	if (process_texture_lines(file + 2) == ERROR)
		return (ERROR);
	if (process_map_lines(file + 6, len - 6) == ERROR)
		return (ERROR);
	return (SUCCES);
}

int	check_file_when_textures_first(char **file, size_t len)
{
	if (process_texture_lines(file) == ERROR)
		return (ERROR);
	if (process_color_lines(file + 4) == ERROR)
		return (ERROR);
	if (process_map_lines(file + 6, len - 6) == ERROR)
		return (ERROR);
	return (SUCCES);
}
