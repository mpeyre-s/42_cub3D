/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:26:51 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/11 16:29:00 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

char	*clean_bank(char *bank)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!bank)
		return (NULL);
	i = 0;
	while (bank[i] != '\n' && bank[i] != '\0')
		i++;
	if (bank[i] == '\0')
		return (free(bank), NULL);
	j = ft_strlen(&bank[i + 1]);
	result = (char *)malloc(j + 1);
	if (!result)
		return (free(bank), NULL);
	j = 0;
	while (bank[++i])
		result[j++] = bank[i];
	result[j] = '\0';
	free(bank);
	return (result);
}

