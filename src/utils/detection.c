/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:59:52 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/10 16:06:34 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_os	detect_os(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	fd = open("/etc/os-release", O_RDONLY);
	if (fd == -1)
	{
		msg("Non-linux environment detected, assuming macOS", TRUE, FALSE, 0);
		return (MACOS);
	}
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (ft_strstr(buffer, "PRETTY_NAME"))
		{
			close(fd);
			msg("Linux environment detected", TRUE, FALSE, 0);
			return (LINUX);
		}
	}
	close(fd);
	msg("Unknown environment detected, assuming linux", TRUE, FALSE, 0);
	return (UNKNOWN);
}
