#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600
# define NAME "mon cub3d"

typedef struct s_data
{
    void *mlx;//connexion a la mlx
    void *win;//pointeur sur une fenetre
}               t_data;

#endif