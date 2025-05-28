/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:08:30 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 15:08:32 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	calcul_distances(void)
{
	s()->r.hauteur = (int)(HEIGHT / s()->r.distance);
	s()->r.mur_haut = -s()->r.hauteur / 2 + HEIGHT / 2;
	if (s()->r.mur_haut < 0)
		s()->r.mur_haut = 0;
	s()->r.mur_bas = s()->r.hauteur / 2 + HEIGHT / 2;
	if (s()->r.mur_bas >= HEIGHT)
		s()->r.mur_bas = HEIGHT - 1;
}

void	draw_vertical_line(int x)
{
	t_texture	*texture;
	double		step;

	calcul_distances();
	texture = select_tex();
	if (s()->r.orientation == 0)
		s()->r.wall_x = s()->p.y + s()->r.distance * s()->r.raydir_y;
	else
		s()->r.wall_x = s()->p.x + s()->r.distance * s()->r.raydir_x;
	s()->r.wall_x -= floor(s()->r.wall_x);
	s()->r.tex_x = (int)(s()->r.wall_x * (double)texture->w);
	if ((s()->r.orientation == 0 && s()->r.raydir_x < 0)
		|| (s()->r.orientation == 1 && s()->r.raydir_y > 0))
		s()->r.tex_x = texture->w - s()->r.tex_x - 1;
	step = 1.0 * texture->h / s()->r.hauteur;
	draw_ceiling(x, s()->r.mur_haut);
	draw_wall(x, s()->r.mur_haut, s()->r.mur_bas, texture);
	draw_floor(x, s()->r.mur_bas);
}
