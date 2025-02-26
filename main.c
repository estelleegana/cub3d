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

void init_player_pos(t_player *player)
{
    player->x = 4.4;
    player->y = 4.4;
    player->angle = 2.2;
}

void cast_ray(t_player *player, double ray_angle)
{
    init_player_pos(player);
    double ray_x = player->x;
    double ray_y = player->y;
    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = sin(ray_angle);

    while (map[(int)ray_y][(int)ray_x] == 0)
    {
        ray_x += ray_dir_x * 0.1;
        ray_y += ray_dir_y * 0.1;
    }

    printf("Ray hit at (%f, %f)\n", ray_x, ray_y);
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

int close_window_cross(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
}

void open_window(t_data data)
{
    t_player player;

    data.mlx = mlx_init();//connexion a la mlx
    if (data.mlx == NULL)
        return;
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, NAME);//creer le fenetre
    if (data.win == NULL)
        return;
    // color_window(data);
    init_player_pos(&player);
    cast_ray(&player, 0.0);
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