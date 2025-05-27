#include "cub3d.h"

void draw_vertical_line(int x, double distance, int orientation, double rayDirX, double rayDirY)
{
    int hauteur = (int)(HEIGHT / distance);
    int hautDuMur = -hauteur / 2 + HEIGHT / 2;
    if (hautDuMur < 0)
        hautDuMur = 0;
    int basDuMur = hauteur / 2 + HEIGHT / 2;
    if (basDuMur >= HEIGHT)
        basDuMur = HEIGHT - 1;

    t_texture *texture;
    if (orientation == 0 && rayDirX > 0) // Est
        texture = &s()->t[2];
    else if (orientation == 0 && rayDirX < 0) // Ouest
        texture = &s()->t[3];
    else if (orientation == 1 && rayDirY > 0) // Sud
        texture = &s()->t[1];
    else // Nord
        texture = &s()->t[0];

    double wallX;
    if (orientation == 0)
        wallX = s()->p.Y + distance * rayDirY;
    else
        wallX = s()->p.X + distance * rayDirX;
    wallX -= floor(wallX);

    int texX = (int)(wallX * (double)texture->w);
    if ((orientation == 0 && rayDirX < 0) || (orientation == 1 && rayDirY > 0))
        texX = texture->w - texX - 1;

    double step = 1.0 * texture->h / hauteur;
    double texPos = (hautDuMur - HEIGHT / 2 + hauteur / 2) * step;
    
    for (int y = hautDuMur; y < basDuMur; y++)
    {
        int texY = (int)texPos & (texture->h - 1);
        texPos += step;
        int color = *(int *)(texture->addr + (texY * texture->line_len + texX * (texture->bpp / 8)));
        put_pixel(x, y, color, s());
    }
}

//pr chaque colonne x de la largeur de l'ecran
void cast_ray(int x)
{
    double cameraX = 2 * x / (double)WIDTH - 1;
    double rayDirX = s()->p.dirX + s()->p.planeX * cameraX;
    double rayDirY = s()->p.dirY + s()->p.planeY * cameraX;
    int mapX = (int)s()->p.X;
    int mapY = (int)s()->p.Y;
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);
    double sideDistX, sideDistY;
    int stepX, stepY;
    double distance;
    double orientation;
    int hit;

    //initialisation DDA
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (s()->p.X - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - s()->p.X) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (s()->p.Y - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - s()->p.Y) * deltaDistY;
    }

    //algo DDA
    hit = 0;
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            orientation = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            orientation = 1;
        }
        if (mapX < 0 || mapY >= s()->map.line || mapY < 0 || mapX >= s()->map.columns)
            break;
        if (s()->map.data[mapY][mapX])
        {
            if(s()->map.data[mapY][mapX] == '1')
                hit = 1;
        }
    }

    if (orientation == 0)
        distance = (mapX - s()->p.X + (1 - stepX) / 2) / rayDirX;
    else
        distance = (mapY - s()->p.Y + (1 - stepY) / 2) / rayDirY;

    draw_vertical_line(x, distance, orientation, rayDirX, rayDirY);
}

int raycasting()
{
    printf("X Y : %f %f\n", s()->p.X, s()->p.Y);
    clear_image();
    for (int x = 0; x < WIDTH; x++)
        // put_tex(3);
        cast_ray(x);
    mlx_put_image_to_window(s()->mlx, s()->win, s()->img, 0,0);
    return 0;
}

