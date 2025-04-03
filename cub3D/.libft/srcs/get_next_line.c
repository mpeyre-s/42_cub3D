/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:26:13 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/11 16:29:04 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

static char	*strdup_to_backslash(char *bank)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	while (bank[len] && bank[len] != '\n')
		len++;
	result = (char *)malloc((len + 2) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = bank[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
}

static char	*read_one_more_time(int fd, char *bank, ssize_t *bytes_read)
{
	char	*buffer;
	char	*new_bank;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(bank), NULL);
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read < 0)
		return (free(buffer), free(bank), NULL);
	buffer[*bytes_read] = '\0';
	new_bank = ft_strjoin(bank, buffer);
	free(buffer);
	if (!new_bank)
		return (free(bank), NULL);
	free(bank);
	return (new_bank);
}

static char	*process_existing_line(char **bank)
{
	char	*new_bank;
	char	*line;

	line = strdup_to_backslash(*bank);
	new_bank = clean_bank(*bank);
	if (!new_bank)
	{
		free(line);
		return (NULL);
	}
	*bank = new_bank;
	return (line);
}

static char	*handle_eof(char **bank)
{
	char	*line;

	if (!bank || !*bank || **bank == '\0')
	{
		if (*bank)
			free(*bank);
		*bank = NULL;
		return (NULL);
	}
	line = ft_strdup(*bank);
	if (!line)
	{
		free(*bank);
		*bank = NULL;
		return (NULL);
	}
	free(*bank);
	*bank = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*bank;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!bank)
	{
		bank = ft_strdup("");
		if (!bank)
			return (NULL);
	}
	while (1)
	{
		if (ft_strchr(bank, '\n'))
			return (process_existing_line(&bank));
		bank = read_one_more_time(fd, bank, &bytes_read);
		if (!bank || bytes_read == 0)
			return (handle_eof(&bank));
	}
}
