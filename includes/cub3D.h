/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:44:06 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/25 18:17:49 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* --------------------------- LIBRAIRIES INCLUDES ---------------------------*/
# include "../.libft/libft.h"
# include "../.minilibx_opengl/mlx.h"
// # include "../.minilibx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

/* ----------------------------- PROGRAM MACROS ------------------------------*/
// # define WINDOW_WIDTH 1920
// # define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720
# define CELL_LENGTH 64
# define FOV 60
# define FOV_SCALE 0.66
# define MOVE_SPEED 0.01
# define ROTATION_SPEED 0.010
# define PI 3.1415926535897932384626437872
# define TEXTURE_EXT ".xpm"

/* ------------------------------- STRUCTURES --------------------------------*/
typedef enum e_os
{
	LINUX,
	MACOS,
	UNKNOWN
}				t_os;

typedef enum e_action
{
	FOWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	TURN_LEFT,
	TURN_RIGHT
}				t_action;

typedef struct s_rgb
{
	u_int8_t	red;
	u_int8_t	green;
	u_int8_t	blue;
}				t_rgb;

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
	size_t	frames;
}				t_mlx;

typedef struct s_txt
{
	void	*img;
	void	*addr;
	int		width; // width de la texture
	int		height; // height de la texture
	int		bpp;
	int		line_length;
	int		endian;
	int		tex_x;
	int		tex_y;
	int		color;
}				t_txt;

typedef struct s_map
{
	int		width;
	int		height;
	int		cell_width;
	int		cell_height;
	int		px_width;
	int		px_height;
	t_rgb	*floor;
	t_rgb	*ceiling;
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
	int		**grid;
	unsigned int	floor_color;
	unsigned int	sky_color;

	t_txt	north;
	t_txt	south;
	t_txt	east;
	t_txt	west;
}				t_map;


typedef struct s_player
{
	char	direction;
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	rotation;
}				t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	len_x;
	double	len_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit_side;
	double	wall_dist;
	int		pxl_height;
	int		wall_start;
	int		wall_end;
	double	wall_norm_x;
	double	wall_norm_y;
}				t_ray;

typedef struct s_keys
{
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
}				t_keys;

typedef struct s_game
{
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
	t_keys		*keys;
	t_txt	gun_texture;
}				t_game;

typedef struct s_init
{
	t_rgb	*floor;
	t_rgb	*ceiling;
	char	*south_texture;
	char	*north_texture;
	char	*east_texture;
	char	*west_texture;
	char	**grid;
	int		width;
	int		height;
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	rotation;
	char	side;
}				t_init;

/* -------------------------- FUNCTIONS PROTOTYPES ---------------------------*/
int		msg(char *msg, int endl, int is_error, int value);
int		print_ascii_art(void);
int		print_keycode_config(t_game *game);

int		parsing(int ac, char **av);
char	*read_file(char *file_path);
int		is_empty_line(char *line);
char	*extract_path(char *line);

int		check_file_when_colors_first(char **file, size_t len);
int		check_file_when_textures_first(char **file, size_t len);

int		process_color_lines(char **file);
int		process_texture_lines(char **file);
int		process_map_lines(char **file, size_t len);

size_t	tab_of_tab_len(char **tab);

t_init	*init_data(char *path);
t_rgb	*get_floor_rgb(char **file);
t_rgb	*get_ceiling_rgb(char **file);
char	*get_south_texture(char **file);
char	*get_north_texture(char **file);
char	*get_east_texture(char **file);
char	*get_west_texture(char **file);
char	**get_map_grid(char **file);
int		get_map_width(char **file);
int		get_map_height(char **file);
double	get_x_pos(char **file);
double	get_y_pos(char **file);
double	get_dirx(char **file);
double	get_diry(char **file);
double	get_rotation(char **file);

t_game	*init(char *map_path);
int		**init_grid(t_init *data, int width, int height);
t_map	*init_map(t_init *data);

int		start_game(t_game *game);
void	update_map(t_game *game);

void	print_grid(t_game *game);
void	fill_grid_with_map(t_game *game);
void	spawn_player(t_game *game);

void	move_player(t_game *game, t_action action);
void	rotate_player(t_game *game, t_action action);

void	exit_program(t_game *game);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		loop_hook(t_game *game);
int		close_hook(t_game *game);

int		start_mlx(t_game *game);
int		destroy_mlx(t_game *game);

void	print_pixel(t_game *game, int x, int y, unsigned int color);
void	color_fill(t_game *game, unsigned int color);
void	draw_square_minimap(t_game *game, int *coords, int size, int color);
void	draw_line(t_game *game, int *start, int *end);
void	draw_rectangle(t_game *game, int *start, int *end, int color);

void	print_minimap(t_game *game);

char	*ft_strstr(const char *haystack, const char *needle);
t_os	detect_os(void);
char	**convert_content(char *content);
void	free_file_tab(char **file, size_t len);
void	free_split(char **split);
int		free_init(t_init *data);
u_int8_t	ft_atouint8(char *str);

void	raycast(t_game *game, t_player *player, int **grid);
void	init_player_direction(t_player *player);
char	get_player_side(char **file);
void	init_textures(t_map *map, t_game *game);
void	handle_txt(int x, t_map *map, t_game *game, t_ray *ray);
void	init_color(t_map *map);
int		init_gun(t_game *game);

/* --------------------------- DEVELOPMENT MACROS ----------------------------*/
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SUCCES 0

# define STR_PARSE1 "Use ./cub3D map_name.cub for running the game"
# define STR_PARSE2 "Invalid map file, use .cub extension + check error messages"

/* ------------------------------- KEY MAPPING -------------------------------*/
# define MAC_FORWARD_KEY 13
# define MAC_BACKWARD_KEY 1
# define MAC_LEFT_KEY 0
# define MAC_RIGHT_KEY 2
# define MAC_ESC_KEY 53
# define MAC_LEFT_ARROW 123
# define MAC_RIGHT_ARROW 124

# define LIN_FORWARD_KEY 119
# define LIN_BACKWARD_KEY 115
# define LIN_LEFT_KEY 97
# define LIN_RIGHT_KEY 100
# define LIN_ESC_KEY 65307
# define LIN_LEFT_ARROW 65361
# define LIN_RIGHT_ARROW 65363

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
