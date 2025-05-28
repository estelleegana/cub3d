/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:54:52 by estegana          #+#    #+#             */
/*   Updated: 2025/05/27 17:54:54 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

//modifie les pixels d'une img en memoire
//(alors que mlx_putpix regenere chaque pixel a chaque appel)
void	put_pixel(int x, int y, int color, t_config *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->pixel_data[index] = color & 0xFF;
	game->pixel_data[index + 1] = (color >> 8) & 0xFF;
	game->pixel_data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(void)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, s());
			x++;
		}
		y++;
	}
}

void	init_raycast_variables(int x)
{
	s()->r.camera_x = 2 * x / (double)WIDTH - 1;
	s()->r.raydir_x = s()->p.dir_x + s()->p.plane_x * s()->r.camera_x;
	s()->r.raydir_y = s()->p.dir_y + s()->p.plane_y * s()->r.camera_x;
	s()->r.map_x = (int)s()->p.x;
	s()->r.map_y = (int)s()->p.y;
	s()->r.deltadist_x = fabs(1 / s()->r.raydir_x);
	s()->r.deltadist_y = fabs(1 / s()->r.raydir_y);
}

void	init_raycast_conditions(void)
{
	if (s()->r.raydir_x < 0)
	{
		s()->r.step_x = -1;
		s()->r.sidedist_x = (s()->p.x - s()->r.map_x) * s()->r.deltadist_x;
	}
	else
	{
		s()->r.step_x = 1;
		s()->r.sidedist_x = (s()->r.map_x
			+ 1.0 - s()->p.x) * s()->r.deltadist_x;
	}
	if (s()->r.raydir_y < 0)
	{
		s()->r.step_y = -1;
		s()->r.sidedist_y = (s()->p.y - s()->r.map_y) * s()->r.deltadist_y;
	}
	else
	{
		s()->r.step_y = 1;
		s()->r.sidedist_y = (s()->r.map_y
			+ 1.0 - s()->p.y) * s()->r.deltadist_y;
	}
}
