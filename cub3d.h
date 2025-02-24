#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>//printf
# include <fcntl.h>//open
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define NAME "cub3d"
# define COLOR 0xFF0000
# define W 119
# define A 97
# define S 115
# define D 100
# define map_w 6
# define map_h 7

//a recuperer du fichier <fichier>.cub
int map[map_w][map_h] =
{
    {1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,3,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1},
};

typedef struct s_data
{
    void *mlx;//connexion a la mlx
    void *win;//pointeur sur une fenetre
    char *NO;//north texture
    char *SO;
    char *WE;
    char *EA;
    int F[3];//couleur du floor
    int C[3];//couleur du ceiling
} t_data;

typedef struct s_player
{
    double x;
    double y;
    double angle;
} t_player;

#endif


//fleches droite et gauche : vue a droite et gauche de la map
//W A S D : bouger ds le labyrhinte
//echap : fermer fenetre et quitter le prog
//crois rouge : fermer fenetre et quitter le prog
//./cub3d 