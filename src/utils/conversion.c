/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:08:14 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/10/01 10:00:00 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include <ctype.h> // For isspace
#include <string.h> // For strncpy

// Configuration struct to control parsing behavior
typedef struct s_parse_config {
    int trim_spaces;        // 1 to trim leading/trailing spaces, 0 to keep them
    int ignore_comments;    // 1 to skip lines starting with '#', 0 to include
    int max_line_length;    // Maximum allowed length per line (0 for no limit)
    int (*validate_line)(char *); // Optional callback to validate each line
} t_parse_config;

// Counts the number of lines based on config settings
static int count_lines(char *content, t_parse_config *config)
{
    int line_count = 0;
    char *line = content;
    int in_line = 0;

    while (*line) {
        if (*line == '\n') {
            if (in_line && !is_empty_line(line + 1))
                line_count++;
            in_line = 0;
        } else {
            in_line = 1;
        }
        line++;
    }
    if (in_line) // Account for the last line if no trailing newline
        line_count++;
    return line_count + 1; // +1 for NULL terminator in result array
}

// Extracts and processes a line according to config settings
static char *extract_line(char *start, char **next, t_parse_config *config)
{
    char *end = start;
    while (*end && *end != '\n')
        end++;
    
    // Handle comment lines
    if (config->ignore_comments && *start == '#') {
        *next = (*end == '\n') ? end + 1 : end;
        return ft_strdup("");
    }

    char *first = start;
    char *last = end - 1;
    if (config->trim_spaces) {
        while (*first && *first != '\n' && ft_isspace(*first))
            first++;
        while (last >= first && ft_isspace(*last))
            last--;
    } else {
        first = start;
        last = end - 1;
    }

    // Check if line is empty or exceeds max length
    if (first > last || *first == '\n' || 
        (config->max_line_length > 0 && (end - start) > config->max_line_length)) {
        *next = (*end == '\n') ? end + 1 : end;
        return ft_strdup("");
    }

    size_t len = last - first + 1;
    char *temp = malloc(len + 1);
    if (!temp) {
        *next = (*end == '\n') ? end + 1 : end;
        return NULL;
    }
    strncpy(temp, first, len);
    temp[len] = '\0';

    // Validate line if callback is provided
    if (config->validate_line && !config->validate_line(temp)) {
        free(temp);
        *next = (*end == '\n') ? end + 1 : end;
        return ft_strdup("");
    }

    *next = (*end == '\n') ? end + 1 : end;
    return temp;
}

// Frees the result array up to index j
static void free_result(char **result, int j)
{
    if (!result)
        return;
    while (j > 0)
        free(result[--j]);
    free(result);
}

// Main function to convert content with customizable options
char **convert_content_ex(char *content, t_parse_config *config, int *error)
{
    char **result;
    char *line;
    char *temp;
    int j;

    if (!content || !config) {
        if (error) *error = 1; // Invalid input
        return NULL;
    }

    int total_lines = count_lines(content, config);
    result = malloc(sizeof(char *) * total_lines);
    if (!result) {
        if (error) *error = 2; // Memory allocation failure
        return NULL;
    }

    j = 0;
    line = content;
    while (*line) {
        temp = extract_line(line, &line, config);
        if (!temp) {
            free_result(result, j);
            if (error) *error = 2; // Memory allocation failure
            return NULL;
        }
        if (ft_strlen(temp) > 0) {
            result[j] = ft_strdup(temp);
            if (!result[j]) {
                free(temp);
                free_result(result, j);
                if (error) *error = 2; // Memory allocation failure
                return NULL;
            }
            j++;
        }
        free(temp);
    }
    result[j] = NULL;
    if (error) *error = 0; // Success
    return result;
}

// Wrapper for original behavior
char **convert_content(char *content)
{
    t_parse_config config = {1, 0, 0, NULL}; // Trim spaces, no comments, no validation
    int error = 0;
    return convert_content_ex(content, &config, &error);
}

// Example validation function for Cub3D map lines
static int validate_map_line(char *line)
{
    while (*line) {
        if (*line != '0' && *line != '1' && *line != ' ' && 
            *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
            return 0; // Invalid character
        line++;
    }
    return 1; // Valid
}

// Example usage with enhanced features
/*
int main(void) {
    char *content = "NO ./north\n# Comment\n  R 1920 1080  \n\n1111\n1001";
    t_parse_config config = {
        .trim_spaces = 1,
        .ignore_comments = 1,
        .max_line_length = 100,
        .validate_line = NULL // or validate_map_line for map lines
    };
    int error = 0;
    char **result = convert_content_ex(content, &config, &error);
    if (!result || error) {
        printf("Error: %d\n", error);
        return 1;
    }
    for (int i = 0; result[i]; i++) {
        printf("Line %d: '%s'\n", i, result[i]);
    }
    free_result(result, count_lines(content, &config) - 1);
    return 0;
}
*/
