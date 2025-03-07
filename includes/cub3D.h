/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:44:06 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/07 17:08:11 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* --------------------------- LIBRAIRIES INCLUDES ---------------------------*/
# include "../.libft/libft.h"
# include "../.minilibx_opengl/mlx.h"
# include <stdio.h>
# include <stdlib.h>

/* ----------------------------- PROGRAM MACROS ------------------------------*/
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* ------------------------------- STRUCTURES --------------------------------*/
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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

/* --------------------------- KEY MAPPING (APPLE) ---------------------------*/
# define FORWARD_KEY 13      /* W key */
# define BACKWARD_KEY 1      /* S key */
# define LEFT_KEY 0         /* A key */
# define RIGHT_KEY 2        /* D key */
# define ESC_KEY 53         /* ESC key */

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
