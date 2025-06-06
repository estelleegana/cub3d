/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:45:08 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 18:45:10 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "includes/libft/libft.h"
# include "includes/mlx/mlx.h"
# include "includes/gnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

# define NAME "CUB3D"
# define WIDTH 1280
# define HEIGHT 720
# define TILE_SIZE 20
# define DEBUG 0
# define ECHAP 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define SPEED 0.01
# define ROT_SPEED 0.01

# define BOLD "\033[1m"
# define RED "\033[38;2;255;0;0m"
# define GREEN "\033[38;2;0;255;0m"
# define RESET "\033[0m"

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture
{
	void	*img;
	char	*path;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_texture;

typedef struct s_color {
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_map
{
	int		line;
	int		columns;
	char	**data;
}	t_map;

typedef struct s_decals {
	t_texture	n;
	t_texture	s;
	t_texture	w;
	t_texture	e;
	t_color		floor_color;
	t_color		ceiling_color;
}	t_decals;

typedef struct s_keys
{
	int	w;
	int	s;
	int	d;
	int	a;
	int	right;
	int	left;
}	t_keys;

typedef struct s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	int		step_x;
	int		step_y;
	double	distance;
	double	orientation;
	int		hauteur;
	int		tex_x;
	int		tex_y;
	int		mur_haut;
	int		mur_bas;
	double	wall_x;
}	t_ray;

typedef struct s_config
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pixel_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_map		map;
	t_decals	decals;
	t_texture	*t;
	t_texture	screen;
	t_player	p;
	t_keys		k;
	t_ray		r;
}	t_config;

//parsing
int			handle_map(char *filename);
int			parse_cub(char *filename);
int			handle_decals(char *filename, t_config *conf);
int			handle_rgb(int identifier, t_config *conf, char **rgb);
int			handle_files(char *line, t_config *conf, int identifier);
int			find_identifier(char *line);
int			parse_identifier(char *line, int identifier0, t_config *conf);
int			check_map(void);

//deplacement (wasd.c rotations.c)
void		key_w(void);
void		key_s(void);
void		key_a(void);
void		key_d(void);
void		key_right(void);
void		key_left(void);

//display (init, esc, red cross, gestion du clavier)
void		open_window(void);
int			close_window_cross(void);
int			close_window_echap(void);
int			key_press(int touche);
int			key_release(int touche);
int			game_loop(void);
void		init_player(void);
void		init_game(void);
void		init_tex(void);

//raycasting
int			rgb_to_hex(t_color color);
void		put_pixel(int x, int y, int color, t_config *game);
void		clear_image(void);
void		draw_vertical_line(int x);
void		init_raycast_variables(int x);
void		init_raycast_conditions(void);
void		cast_ray(int x);
int			raycasting(void);
void		draw_ceiling(int x, int mur_haut);
void		draw_wall(int x, int mur_haut, int mur_bas, t_texture *texture);
void		draw_floor(int x, int mur_bas);

//utils : singleton
t_config	*s(void);
//utils : free
void		free_map(void);
void		free_textures(void);
void		free_decals_map(void);
void		free_decals(void);
void		free_gnl(char *get_nextline, int fd_decals);

#endif
