#include "cub3d.h"

unsigned int valid_map(char **argv)
{
    if (ft_strcmp(argv, "ouiii") == 0)
        return 1;
    else
        return 0;
}

void open_window()
{
    void *mlxptr;//connexion a la mlx
    void *winptr;//fenetre

    mlxptr = mlx_init();//connexion a la mlx
    winptr = mlx_new_window(mlxptr, WIDTH, HEIGHT, NAME);//creer le fenetre
    mlx_loop(mlxptr);//la garder ouverte
}


int main(int argc, char **argv)
{
    if (argc != 2)
        printf("program must take a map in format *.cub as a parameter\n");
    else
    {
        if (!valid_map(argv[1]))
            printf("enter a valid map\n");
        else
            open_window();
    }   
}  