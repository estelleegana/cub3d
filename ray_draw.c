/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:22:50 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 15:22:52 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(int x, int mur_haut)
{
	int	c;

	c = 0;
	while (c < mur_haut)
	{
		put_pixel(x, c, rgb_to_hex(s()->decals.ceiling_color), s());
		c++;
	}	
}

void	draw_wall(int x, int mur_haut, int mur_bas, t_texture *texture)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	step = 1.0 * texture->h / s()->r.hauteur;
	tex_pos = (mur_haut - HEIGHT / 2 + s()->r.hauteur / 2) * step;
	y = mur_haut;
	while (y <= mur_bas)
	{
		s()->r.tex_y = (int)tex_pos & (texture->h - 1);
		tex_pos += step;
		color = *(int *)(texture->addr + (s()->r.tex_y
					* texture->line_len + s()->r.tex_x * (texture->bpp / 8)));
		put_pixel(x, y, color, s());
		y++;
	}
}

void	draw_floor(int x, int mur_bas)
{
	int	f;

	if (mur_bas >= HEIGHT || mur_bas < 0)
		mur_bas = HEIGHT;
	f = mur_bas + 1;
	while (f < HEIGHT)
	{
		put_pixel(x, f, rgb_to_hex(s()->decals.floor_color), s());
		f++;
	}
}
