#include "cub3d.h"

int rgb_to_hex(t_color color)
{
    return (color.r << 16) + (color.g << 8) + color.b;
}

//modifie les pixels d'une img en memoire
//(alors que mlx_putpix regenere chaque pixel a chaque appel)
void put_pixel(int x, int y, int color, t_config *game)
{
    int index;

    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    index = y * game->size_line + x * game->bpp / 8;
    game->pixel_data[index] = color & 0xFF;
    game->pixel_data[index + 1] = (color >> 8) & 0xFF;
    game->pixel_data[index + 2] = (color >> 16) & 0xFF;
}

//test si les bonnes tex ont ete chargees (affiche la t[i] au milieu de lecran)
//x = WIDTH
//y = HEIGHT
// void put_tex(int i)
// {
//     int start_x = (WIDTH - s()->t[i].w) / 2;
//     int start_y = (HEIGHT - s()->t[i].h) / 2;

//     for (int y = 0; y < s()->t[i].h; y++)
//     {
//         for (int x = 0; x < s()->t[i].w; x++)
//         {
//             int p = y * s()->t[i].line_len + x * (s()->t[i].bpp / 8);
//             int color = *(int *)(s()->t[i].addr + p);
//             put_pixel(start_x + x, start_y + y, color, s());
//         }
//     }
// }


void clear_image()
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, s());
}