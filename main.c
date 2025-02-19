#include "cub3d.h"

unsigned int valid_map(char **argv)
{
    if (ft_strcmp(argv, "ouiii") == 0)
        return 1;
    else
        return 0;
}

int close_window_echap(int touche, t_data *data)
{
    if (touche == 65307)
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    return (0);
}

int close_window_cross(int x, int y, t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

void open_window(t_data data)
{

    data.mlx = mlx_init();//connexion a la mlx
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, NAME);//creer le fenetre
    mlx_key_hook(data.win, close_window_echap, &data);
    mlx_hook(data.win, 17, 0L, close_window_cross, &data);//17 = fermeture de la fenetre
    mlx_loop(data.mlx);//la garder ouverte
}


int main(int argc, char **argv)
{
    t_data  data;

    if (argc != 2)
        printf("program must take a map in format *.cub as a parameter\n");
    else
    {
        if (!valid_map(argv[1]))
            printf("enter a valid map\n");
        else
            open_window(data);
    }   
}  