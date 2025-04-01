/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:23:55 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/01 16:31:10 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

static int	check_chars_and_player(char **file, size_t len)
{
	size_t	i;
	size_t	j;
	int		player_count;

	i = 0;
	player_count = 0;
	while (i < len && file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] != '0' && file[i][j] != '1' && file[i][j] != ' '
				&& file[i][j] != 'N' && file[i][j] != 'S'
				&& file[i][j] != 'E' && file[i][j] != 'W')
				return (msg("Invalid character in map", TRUE, TRUE, ERROR));
			if (file[i][j] == 'N' || file[i][j] == 'S'
				|| file[i][j] == 'E' || file[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (msg("Map must contain exactly one player position", 1, 1, -1));
	return (SUCCES);
}

static	int	is_full_of_char(char *str, char c)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
			return (FALSE);
	}
	return (TRUE);
}

static int	check_map_is_rectangle(char **file)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(file[0]);
	while (file[++i])
	{
		if (ft_strlen(file[i]) != len)
			return (ERROR);
	}
	return (SUCCES);
}

static int	check_map_integrity(char **file, size_t tab_len)
{
	size_t	i;
	size_t	len;

	i = 1;
	if (tab_len == 0 || !file[0] || is_full_of_char(file[0], '1') == FALSE)
		return (ERROR);
	while (i < (tab_len - 1) && file[i])
	{
		len = ft_strlen(file[i]);
		if (len < 3)
			return (ERROR);
		if (file[i][0] != '1' || file[i][len - 1] != '1')
			return (ERROR);
		i++;
	}
	if (i == 1 || !file[tab_len - 1]
		|| is_full_of_char(file[tab_len - 1], '1') == FALSE)
		return (ERROR);
	return (SUCCES);
}

int	process_map_lines(char **file, size_t len)
{
	if (check_chars_and_player(file, len) == ERROR)
		return (ERROR);
	if (check_map_is_rectangle(file) == ERROR)
	{
		msg("Map isnt a rectangle", TRUE, TRUE, ERROR);
		return (ERROR);
	}
	if (check_map_integrity(file, len) == ERROR)
	{
		msg("Map isnt entierely closed by walls", TRUE, TRUE, ERROR);
		return (ERROR);
	}
	return (SUCCES);
}
