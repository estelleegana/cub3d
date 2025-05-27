#include "cub3d.h"

void	draw_vertical_line(int x, double distance, int orientation, double raydir_x, double raydir_y)
{
	int hauteur = (int)(HEIGHT / distance);
	int hautDuMur = -hauteur / 2 + HEIGHT / 2;
	if (hautDuMur < 0)
		hautDuMur = 0;
	int basDuMur = hauteur / 2 + HEIGHT / 2;
	if (basDuMur >= HEIGHT)
		basDuMur = HEIGHT - 1;

	t_texture *texture;
	if (orientation == 0 && raydir_x > 0) // Est
		texture = &s()->t[2];
	else if (orientation == 0 && raydir_x < 0) // Ouest
		texture = &s()->t[3];
	else if (orientation == 1 && raydir_y > 0) // Sud
		texture = &s()->t[1];
	else // Nord
		texture = &s()->t[0];

	double wallX;
	if (orientation == 0)
		wallX = s()->p.Y + distance * raydir_y;
	else
		wallX = s()->p.X + distance * raydir_x;
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)texture->w);
	if ((orientation == 0 && raydir_x < 0) || (orientation == 1 && raydir_y > 0))
		texX = texture->w - texX - 1;

	double step = 1.0 * texture->h / hauteur;
	double texPos = (hautDuMur - HEIGHT / 2 + hauteur / 2) * step;
	
	for (int c = 0; c < hautDuMur; c++)
		put_pixel(x, c, rgb_to_hex(s()->decals.ceiling_color), s());

	for (int y = hautDuMur; y < basDuMur; y++)
	{
		int texY = (int)texPos & (texture->h - 1);
		texPos += step;
		int color = *(int *)(texture->addr + (texY * texture->line_len + texX * (texture->bpp / 8)));
		put_pixel(x, y, color, s());
	}
	for (int f = basDuMur; f < HEIGHT; f++)
		put_pixel(x, f, rgb_to_hex(s()->decals.floor_color), s());
}

//pr chaque colonne x de la largeur de l'ecran
void cast_ray(int x)
{
	double cameraX = 2 * x / (double)WIDTH - 1;
	double raydir_x = s()->p.dir_x + s()->p.plane_x * cameraX;
	double raydir_y = s()->p.dir_y + s()->p.plane_y * cameraX;
	int mapX = (int)s()->p.X;
	int mapY = (int)s()->p.Y;
	double deltaDistX = fabs(1 / raydir_x);
	double deltaDistY = fabs(1 / raydir_y);
	double sideDistX, sideDistY;
	int stepX, stepY;
	double distance;
	double orientation;
	int hit;

	//initialisation DDA
	if (raydir_x < 0)
	{
		stepX = -1;
		sideDistX = (s()->p.X - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - s()->p.X) * deltaDistX;
	}
	if (raydir_y < 0)
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
		distance = (mapX - s()->p.X + (1 - stepX) / 2) / raydir_x;
	else
		distance = (mapY - s()->p.Y + (1 - stepY) / 2) / raydir_y;

	draw_vertical_line(x, distance, orientation, raydir_x, raydir_y);
}

int raycasting()
{
	clear_image();
	for (int x = 0; x < WIDTH; x++)
		// put_tex(3);
		cast_ray(x);
	mlx_put_image_to_window(s()->mlx, s()->win, s()->img, 0,0);
	return 0;
}

