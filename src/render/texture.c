/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:21:29 by spike             #+#    #+#             */
/*   Updated: 2025/03/22 14:21:33 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

typedef struct s_map
{
	int		width;
	int		height;
	int		cell_width;
	int		cell_height;
	int		px_width;
	int		px_height;
	int		ceiling_color[3];
	int		floor_color[3];
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
	int		**grid;

	t_txt	north;
	t_txt	south;
	t_txt	east;
	t_txt	west;
}				t_map;

typedef struct s_txt
{
	void	*img;
	void	*addr;
	int		width; // width de la texture
	int		height; // height de la texture
	int		bpp;
	int		line_length;
	int		endian;
	int		nb_pixel;
}				t_txt;

void	init_textures(t_map *map, t_game *game, t_ray *ray)
{
	map->north.img = mlx_xpm_file_to_image(game->mlx, map->NO_path, &map->north.width, &map->north.height);
	map->south.img = mlx_xpm_file_to_image(game->mlx, map->SO_path, &map->south.width, &map->south.height);
	map->east.img = mlx_xpm_file_to_image(game->mlx, map->EA_path, &map->east.width, &map->east.height);
	map->west.img = mlx_xpm_file_to_image(game->mlx, map->WE_path, &map->west.width, &map->west.height);
	if (!map->north.img || !map->south.img || !map->east.img || !map->west.img)
	{
		printf("Erreur : Impossible de charger l'une des textures.\n");
		exit(1);
	}
	map->north.addr = mlx_get_data_addr(map->north.img, &map->north.bpp, &map->north.line_length, &map->north.endian);
	map->south.addr = mlx_get_data_addr(map->south.img, &map->south.bpp, &map->south.line_length, &map->south.endian);
	map->east.addr = mlx_get_data_addr(map->east.img, &map->east.bpp, &map->east.line_length, &map->east.endian);
	map->west.addr = mlx_get_data_addr(map->west.img, &map->west.bpp, &map->west.line_length, &map->west.endian);

	if (ray->hit_side == -1)
		map->north.nb_pixel = (int)(ray->wall_hit * map->north.width);
	else if (ray->hit_side == -2)
		map->south.nb_pixel = (int)(ray->wall_hit * map->south.width);
	else if (ray->hit_side == 1)
		map->east.nb_pixel = (int)(ray->wall_hit * map->east.width);
	else if (ray->hit_side == 2)
		map->west.nb_pixel = (int)(ray->wall_hit * map->west.width);

}
void	init_txt_pixel(t_map *map, t_ray *ray)
{
	if (ray->hit_side == -1)
		map->north.nb_pixel = (int)(ray->wall_hit * map->north.width);
	else if (ray->hit_side == -2)
		map->south.nb_pixel = (int)(ray->wall_hit * map->south.width);
	else if (ray->hit_side == 1)
		map->east.nb_pixel = (int)(ray->wall_hit * map->east.width);
	else if (ray->hit_side == 2)
		map->west.nb_pixel = (int)(ray->wall_hit * map->west.width);
}

void	handle_txt(t_map *map, t_game *game, t_ray *ray)
{
	init_textures(map, game, ray);
	init_txt_pixel(map, ray);
}
