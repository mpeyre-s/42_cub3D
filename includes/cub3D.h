/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:44:06 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/08 19:22:24 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* --------------------------- LIBRAIRIES INCLUDES ---------------------------*/
# include "../.libft/libft.h"
# include "../.minilibx_opengl/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

/* ----------------------------- PROGRAM MACROS ------------------------------*/
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* ------------------------------- STRUCTURES --------------------------------*/
typedef enum e_os
{
	LINUX,
	MACOS,
	UNKNOWN
}				t_os;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_os	os;
}				t_mlx;

typedef struct s_map
{
	int		width;
	int		height;
	int		ceiling_color[3];
	int		floor_color[3];
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
	int		**grid;
}				t_map;

typedef struct s_game
{
	t_mlx	*mlx;
	t_map	*map;
}				t_game;

/* -------------------------- FUNCTIONS PROTOTYPES ---------------------------*/
int		msg(char *msg, int endl, int is_error, int value);
int		print_ascii_art(void);
int		print_keycode_config(t_game *game);

int		parsing(int ac, char **av);

t_game	*init(char *map_path);


int		start_game(t_game *game);

void	exit_program(t_game *game);

int		key_hook(int keycode, t_game *game);
int		close_hook(t_game *game);

int		start_mlx(t_game *game);
int		destroy_mlx(t_game *game);

/* --------------------------- DEVELOPMENT MACROS ----------------------------*/
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SUCCES 0

# define STR_PARSE1 "Use ./cub3D map_name.cub for running the game"
# define STR_PARSE2 "Invalid map, use .cub extension + check the map syntax"

/* ------------------------------- KEY MAPPING -------------------------------*/
# define MAC_FORWARD_KEY 13
# define MAC_BACKWARD_KEY 1
# define MAC_LEFT_KEY 0
# define MAC_RIGHT_KEY 2
# define MAC_ESC_KEY 53

# define LIN_FORWARD_KEY 119
# define LIN_BACKWARD_KEY 115
# define LIN_LEFT_KEY 97
# define LIN_RIGHT_KEY 100
# define LIN_ESC_KEY 65307

/* --------------------------- ASCII ART / COLORS ----------------------------*/
# define RESET_COLOR "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"

# define ASCII_L1 "\n \033[38;5;51m ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \n"
# define ASCII_L2 "\033[38;5;45m ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n"
# define ASCII_L3 "\033[38;5;39m ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n"
# define ASCII_L4 "\033[38;5;33m ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n"
# define ASCII_L5 "\033[38;5;63m ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n"
# define ASCII_L6 "\033[38;5;57m ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝\n\n"

#endif
