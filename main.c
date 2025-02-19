#include "cub3d.h"

int main()
{
    void *mlxptr;//connexion a la mlx
    void *winptr;//fenetre

    mlxptr = mlx_init();//connexion a la mlx
    winptr = mlx_new_window(mlxptr, WIDTH, HEIGHT, NAME);//creer le fenetre
    mlx_loop(mlxptr);//la garder ouverte
}