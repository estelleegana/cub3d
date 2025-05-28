#include "cub3d.h"

void	draw_vertical_line(int x)
{
	int	h;
	int	mur_haut;
	int	mur_bas;
	t_texture *texture;

	h = (int)(HEIGHT / s()->r.distance);
	mur_haut = -h / 2 + HEIGHT / 2;
	if (mur_haut < 0)
		mur_haut = 0;
	mur_bas = h / 2 + HEIGHT / 2;
	if (mur_bas >= HEIGHT)
		mur_bas = HEIGHT - 1;

	if (s()->r.orientation == 0 && s()->r.raydir_x > 0)
		texture = &s()->t[2];
	else if (s()->r.orientation == 0 && s()->r.raydir_x < 0)
		texture = &s()->t[3];
	else if (s()->r.orientation == 1 && s()->r.raydir_y > 0)
		texture = &s()->t[1];
	else
		texture = &s()->t[0];

	double wallX;
	if (s()->r.orientation == 0)
		wallX = s()->p.y + s()->r.distance * s()->r.raydir_y;
	else
		wallX = s()->p.x + s()->r.distance * s()->r.raydir_x;
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)texture->w);
	if ((s()->r.orientation == 0 && s()->r.raydir_x < 0) || (s()->r.orientation == 1 && s()->r.raydir_y > 0))
		texX = texture->w - texX - 1;

	double step = 1.0 * texture->h / h;
	double texPos = (mur_haut - HEIGHT / 2 + h / 2) * step;
	
	for (int c = 0; c < mur_haut; c++)
		put_pixel(x, c, rgb_to_hex(s()->decals.ceiling_color), s());

	for (int y = mur_haut; y < mur_bas; y++)
	{
		int texY = (int)texPos & (texture->h - 1);
		texPos += step;
		int color = *(int *)(texture->addr + (texY * texture->line_len + texX * (texture->bpp / 8)));
		put_pixel(x, y, color, s());
	}
	for (int f = mur_bas; f < HEIGHT; f++)
		put_pixel(x, f, rgb_to_hex(s()->decals.floor_color), s());
}

void	init_raycast(int x)
{
	s()->r.camera_x = 2 * x / (double)WIDTH - 1;
	s()->r.raydir_x = s()->p.dir_x + s()->p.plane_x * s()->r.camera_x;
	s()->r.raydir_y = s()->p.dir_y + s()->p.plane_y * s()->r.camera_x;
	s()->r.map_x = (int)s()->p.x;
	s()->r.map_y = (int)s()->p.y;
	s()->r.deltadist_x = fabs(1 / s()->r.raydir_x);
	s()->r.deltadist_y = fabs(1 / s()->r.raydir_y);
}

void cast_ray(int x)
{
	int hit;

	init_raycast(x);
	if (s()->r.raydir_x < 0)
	{
		s()->r.step_x = -1;
		s()->r.sidedist_x = (s()->p.x - s()->r.map_x) * s()->r.deltadist_x;
	}
	else
	{
		s()->r.step_x = 1;
		s()->r.sidedist_x = (s()->r.map_x + 1.0 - s()->p.x) * s()->r.deltadist_x;
	}
	if (s()->r.raydir_y < 0)
	{
		s()->r.step_y = -1;
		s()->r.sidedist_y = (s()->p.y - s()->r.map_y) * s()->r.deltadist_y;
	}
	else
	{
		s()->r.step_y = 1;
		s()->r.sidedist_y = (s()->r.map_y + 1.0 - s()->p.y) * s()->r.deltadist_y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (s()->r.sidedist_x < s()->r.sidedist_y)
		{
			s()->r.sidedist_x += s()->r.deltadist_x;
			s()->r.map_x += s()->r.step_x;
			s()->r.orientation = 0;
		}
		else
		{
			s()->r.sidedist_y += s()->r.deltadist_y;
			s()->r.map_y += s()->r.step_y;
			s()->r.orientation = 1;
		}
		if (s()->r.map_x < 0 || s()->r.map_y >= s()->map.line || s()->r.map_y < 0 || s()->r.map_x >= s()->map.columns)
			break ;
		if (s()->map.data[s()->r.map_y][s()->r.map_x])
		{
			if (s()->map.data[s()->r.map_y][s()->r.map_x] == '1')
				hit = 1;
		}
	}
	if (s()->r.orientation == 0)
		s()->r.distance = (s()->r.map_x - s()->p.x + (1 - s()->r.step_x) / 2) / s()->r.raydir_x;
	else
		s()->r.distance = (s()->r.map_y - s()->p.y + (1 - s()->r.step_y) / 2) / s()->r.raydir_y;
	draw_vertical_line(x);
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
