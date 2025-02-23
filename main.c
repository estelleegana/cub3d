#include "cub3d.h"

void color_window(t_data data)
{
    int x;
    int y;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
            mlx_pixel_put(data.mlx, data.win, x, y, COLOR);
    }
}

// void recup_data(int fd)
// {

// }

// unsigned int valid_scenedescription(int fd)
// {
//     if (recup_data(fd))
//         return 1;
//     else
//         return 0;
// }

int close_window_echap(int touche, t_data *data)
{
    if (touche == 65307)
    {
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);//detruit la connexion a mlx
        free(data->mlx);
        exit(0);
    }
}

int close_window_cross(int x, int y, t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    exit(0);
}

void open_window(t_data data)
{

    data.mlx = mlx_init();//connexion a la mlx
    if (data.mlx == NULL)
        return;
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, NAME);//creer le fenetre
    if (data.win == NULL)
        return;
    // color_window(data);
    mlx_key_hook(data.win, close_window_echap, &data);
    mlx_hook(data.win, 17, 0L, close_window_cross, &data);//17 = fermeture de la fenetre
    mlx_loop(data.mlx);//la garder ouverte
}


int main(int argc, char **argv)
{
    t_data  data;
    int fd;

    if (argc != 2)  
        printf("program must take a map in format *.cub as a parameter\n");
    else
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            perror(argv[1]);
        else
        {
            // if (!valid_scenedescription(fd))
            //     printf("enter a valid map\n");
            // else
                open_window(data);
        }
        close(fd);
    }   
}  