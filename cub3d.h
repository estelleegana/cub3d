#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>//printf
# include <fcntl.h>//open
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define NAME "mon cub3d"
# define COLOR 0xFF0000

typedef struct s_data
{
    void *mlx;//connexion a la mlx
    void *win;//pointeur sur une fenetre
}               t_data;

#endif


//fleches droite et gauche : vue a droite et gauche de la map
//W A S D : bouger ds le labyrhinte
//echap : fermer fenetre et quitter le prog
//crois rouge : fermer fenetre et quitter le prog
//./cub3d 