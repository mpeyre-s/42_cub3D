/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:55:17 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/19 10:45:53 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	free_file_tab(char **file, size_t len)
{
	len++;
	while (len--)
		free(file[len]);
	free(file);
}

int	check_cub_extension(char *filename)
{
	int	len;

	if (!filename)
		return (ERROR);
	len = ft_strlen(filename);
	if (len < 5)
		return (ERROR);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (ERROR);
	return (SUCCES);
}

int	is_file_valid(char *filename)
{
	char	*file_inline;
	char	**file;
	size_t	len;
	int		result;

	file_inline = read_file(filename);
	if (!file_inline)
		return (ERROR);
	file = convert_content(file_inline);
	if (!file)
		return (ERROR);
	len = -1;
	result = ERROR;
	while (file[len])
		++len;
	if (len > 8)
	{
		if (file[0][0] == 'F' || file[0][0] == 'C')
			result = check_file_when_colors_first(file, len);
		else if (file[0][0] == 'S' || file[0][0] == 'N'
			|| file[0][0] == 'E' || file[0][0] == 'W')
			result = check_file_when_textures_first(file, len);
	}
	free_file_tab(file, len);
	return (free(file_inline), result);
}

int	parsing(int ac, char **av)
{
	if (ac != 2)
		return (msg(STR_PARSE1, TRUE, TRUE, ERROR));
	if (check_cub_extension(av[1]) == ERROR)
		return (msg("Error: Not a .cub file", TRUE, TRUE, ERROR));
	if (is_file_valid(av[1]) == ERROR)
		return (msg(STR_PARSE2, TRUE, TRUE, ERROR));
	return (SUCCES);
}
