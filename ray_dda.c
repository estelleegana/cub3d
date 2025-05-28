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
	if (orientation == 0 && raydir_x > 0)
		texture = &s()->t[2];
	else if (orientation == 0 && raydir_x < 0)
		texture = &s()->t[3];
	else if (orientation == 1 && raydir_y > 0)
		texture = &s()->t[1];
	else
		texture = &s()->t[0];

	double wallX;
	if (orientation == 0)
		wallX = s()->p.y + distance * raydir_y;
	else
		wallX = s()->p.x + distance * raydir_x;
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
	int mapX = (int)s()->p.x;
	int mapY = (int)s()->p.y;
	double deltaDistX = fabs(1 / raydir_x);
	double deltaDistY = fabs(1 / raydir_y);
	double sideDistX, sideDistY;
	int stepX, stepY;
	double distance;
	double orientation;
	int hit;
	
	if (raydir_x < 0)
	{
		stepX = -1;
		sideDistX = (s()->p.x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - s()->p.x) * deltaDistX;
	}
	if (raydir_y < 0)
	{
		stepY = -1;
		sideDistY = (s()->p.y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - s()->p.y) * deltaDistY;
	}
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
			break ;
		if (s()->map.data[mapY][mapX])
		{
			if (s()->map.data[mapY][mapX] == '1')
				hit = 1;
		}
	}
	if (orientation == 0)
		distance = (mapX - s()->p.x + (1 - stepX) / 2) / raydir_x;
	else
		distance = (mapY - s()->p.y + (1 - stepY) / 2) / raydir_y;
	draw_vertical_line(x, distance, orientation, raydir_x, raydir_y);
}

int	raycasting(void)
{
	int	x;

	x = 0;
	clear_image();
	while (x < WIDTH)
	{
		cast_ray(x);
		x++;
	}
	mlx_put_image_to_window(s()->mlx, s()->win, s()->img, 0, 0);
	return (0);
}
