/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:58:28 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/27 14:30:34 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Finds the first occurrence of the substring 'needle' in the string 'haystack'
 * @param haystack The string to be searched
 * @param needle The substring to search for
 * @return A pointer to the first occurrence of 'needle' in 'haystack',
 *         or NULL if 'needle' is not found
 */
char *ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

static int	ft_get_digit(char c, int base)
{
	int digit;

	if (c >= '0' && c <= '9')
		digit = c - '0';
	else if (c >= 'A' && c <= 'Z')
		digit = c - 'A' + 10;
	else if (c >= 'a' && c <= 'z')
		digit = c - 'a' + 10;
	else
		return (-1);
	if (digit < base)
		return digit;
	return -1;
}
/**
 * Converts a string to a long integer
 * @param str The string to convert
 * @param endptr If not NULL, stores the address of the first invalid character
 * @param base The base for conversion (between 2 and 36)
 * @return The converted long integer
 */
long	ft_strol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	while ((digit = ft_get_digit(*str, base)) >= 0)
	{
		result = result * base + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

/**
 * Converts a string to an unsigned 8-bit integer
 * @param str The string to convert
 * @return The converted unsigned 8-bit integer, or 0 if the conversion fails
 */
u_int8_t	ft_atouint8(char *str)
{
	int		num;
	char	*endptr;

	num = ft_strol(str, &endptr, 10);
	if (*endptr != '\0' || num < 0)
		return (0);
	if (num > 255)
		return (255);
	return ((u_int8_t)num);
}

/**
 * Copies the string pointed to by src to the buffer pointed to by dest
 * @param dest The destination buffer
 * @param src The source string
 * @return A pointer to the destination buffer
 */
char	*ft_strcpy(char *dest, const char *src)
{
	char *start;

	start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}
