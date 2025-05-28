#include "cub3d.h"

void	draw_ceiling(int x, int mur_haut)
{
	int	c;
	// for (int c = 0; c < mur_haut; c++)
	c = 0;
	while (c < mur_haut)
	{
		put_pixel(x, c, rgb_to_hex(s()->decals.ceiling_color), s());
		c++;
	}	
}

void	draw_wall(int x, int mur_haut, int mur_bas, t_texture *texture)
{
	double step = 1.0 * texture->h / s()->r.hauteur;
	double		texPos;
	texPos = (mur_haut - HEIGHT / 2 + s()->r.hauteur / 2) * step;
	for (int y = mur_haut; y < mur_bas; y++)
	{
		s()->r.tex_y = (int)texPos & (texture->h - 1);
		texPos += step;
		int color = *(int *)(texture->addr + (s()->r.tex_y * texture->line_len + s()->r.tex_x * (texture->bpp / 8)));
		put_pixel(x, y, color, s());
	}
}

void	draw_floor(int x, int mur_bas)
{
	int	f;
	// for (int f = mur_bas; f < HEIGHT; f++)
	f = mur_bas;
	while (f < HEIGHT)
	{
		put_pixel(x, f, rgb_to_hex(s()->decals.floor_color), s());
		f++;
	}
}

t_texture	*select_tex(void)
{
	t_texture	*right_tex;

	if (s()->r.orientation == 0 && s()->r.raydir_x > 0)
		right_tex = &s()->t[2];
	else if (s()->r.orientation == 0 && s()->r.raydir_x < 0)
		right_tex = &s()->t[3];
	else if (s()->r.orientation == 1 && s()->r.raydir_y > 0)
		right_tex = &s()->t[1];
	else
		right_tex = &s()->t[0];
	return (right_tex);
}

void	draw_vertical_line(int x)
{
	int			mur_haut;
	int			mur_bas;
	t_texture	*texture;
	double		wallX;
	double		step;

	s()->r.hauteur = (int)(HEIGHT / s()->r.distance);
	mur_haut = -s()->r.hauteur / 2 + HEIGHT / 2;
	if (mur_haut < 0)
		mur_haut = 0;
	mur_bas = s()->r.hauteur / 2 + HEIGHT / 2;
	if (mur_bas >= HEIGHT)
		mur_bas = HEIGHT - 1;
	texture = select_tex();
	if (s()->r.orientation == 0)
		wallX = s()->p.y + s()->r.distance * s()->r.raydir_y;
	else
		wallX = s()->p.x + s()->r.distance * s()->r.raydir_x;
	wallX -= floor(wallX);
	s()->r.tex_x = (int)(wallX * (double)texture->w);
	if ((s()->r.orientation == 0 && s()->r.raydir_x < 0) || (s()->r.orientation == 1 && s()->r.raydir_y > 0))
		s()->r.tex_x = texture->w - s()->r.tex_x - 1;

	step = 1.0 * texture->h / s()->r.hauteur;
	// texPos = (mur_haut - HEIGHT / 2 + h / 2) * step;
	// for (int c = 0; c < mur_haut; c++)
	// 	put_pixel(x, c, rgb_to_hex(s()->decals.ceiling_color), s());
	draw_ceiling(x, mur_haut);
	// for (int y = mur_haut; y < mur_bas; y++)
	// {
	// 	int texY = (int)texPos & (texture->h - 1);
	// 	texPos += step;
	// 	int color = *(int *)(texture->addr + (texY * texture->line_len + texX * (texture->bpp / 8)));
	// 	put_pixel(x, y, color, s());
	// }
	draw_wall(x, mur_haut, mur_bas, texture);
	// for (int f = mur_bas; f < HEIGHT; f++)
	// 	put_pixel(x, f, rgb_to_hex(s()->decals.floor_color), s());
	draw_floor(x, mur_bas);
}
