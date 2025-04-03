/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:23:26 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/04/01 16:34:23 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

static int	check_lenghts(char **file)
{
	size_t	i;

	i = -1;
	while (++i < 4)
	{
		if (ft_strlen(file[i]) < 7)
			return (ERROR);
	}
	return (SUCCES);
}

static int	check_cardinal_directions(char **file)
{
	int		so;
	int		no;
	int		ea;
	int		we;
	size_t	i;

	so = 0;
	no = 0;
	ea = 0;
	we = 0;
	i = -1;
	while (++i < 4)
	{
		if (ft_strncmp(file[i], "SO", 2) == 0)
			so++;
		else if (ft_strncmp(file[i], "NO", 2) == 0)
			no++;
		else if (ft_strncmp(file[i], "EA", 2) == 0)
			ea++;
		else if (ft_strncmp(file[i], "WE", 2) == 0)
			we++;
	}
	if (so == 1 && no == 1 && ea == 1 && we == 1)
		return (SUCCES);
	return (ERROR);
}

static int	check_img_extension(char **file)
{
	size_t	i;
	size_t	ext_len;
	size_t	cur_len;
	char	*cur_ext;

	i = -1;
	ext_len = ft_strlen(TEXTURE_EXT);
	while (++i < 4)
	{
		cur_len = ft_strlen(file[i]);
		cur_ext = ft_substr(file[i], cur_len - ext_len, ext_len);
		if (!cur_ext)
			return (ERROR);
		if (ft_strncmp(cur_ext, TEXTURE_EXT, cur_len) != 0)
		{
			free(cur_ext);
			return (ERROR);
		}
		free(cur_ext);
	}
	return (SUCCES);
}

static int	check_openability(char **file)
{
	size_t	i;
	size_t	path_len;
	char	*path;
	int		fd;

	i = -1;
	while (++i < 4)
	{
		path_len = ft_strlen(file[i]) - 2;
		path = ft_substr(file[i], 2, path_len);
		if (!path)
			return (ERROR);
		fd = open(path, O_RDONLY);
		if (fd < 0)
		{
			free(path);
			return (ERROR);
		}
		free(path);
	}
	return (SUCCES);
}

int	process_texture_lines(char **file)
{
	if (check_lenghts(file) == ERROR)
	{
		msg("Make sure include texture path", TRUE, TRUE, ERROR);
		return (ERROR);
	}
	if (check_cardinal_directions(file) == ERROR)
	{
		msg("Invalid(s) cardinal directions ID", TRUE, TRUE, ERROR);
		return (ERROR);
	}
	if (check_img_extension(file) == ERROR)
	{
		msg("Invalid texture extension", TRUE, TRUE, ERROR);
		return (ERROR);
	}
	if (check_openability(file) == ERROR)
	{
		msg("Texture file unopenable/inexiting", TRUE, TRUE, ERROR);
		return (ERROR);
	}
	return (SUCCES);
}
