/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:16:26 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 14:59:16 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	orientation(void)
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
}

void	hit_wall(void)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		orientation();
		if (s()->r.map_x < 0 || s()->r.map_y >= s()->map.line
			|| s()->r.map_y < 0 || s()->r.map_x >= s()->map.columns)
			break ;
		if (s()->map.data[s()->r.map_y][s()->r.map_x])
		{
			if (s()->map.data[s()->r.map_y][s()->r.map_x] == '1')
				hit = 1;
		}
	}
}

void	cast_ray(int x)
{
	init_raycast_variables(x);
	init_raycast_conditions();
	hit_wall();
	if (s()->r.orientation == 0)
	{
		s()->r.distance = (s()->r.map_x
			- s()->p.x + (1 - s()->r.step_x) / 2) / s()->r.raydir_x;
	}
	else
	{
		s()->r.distance = (s()->r.map_y
			- s()->p.y + (1 - s()->r.step_y) / 2) / s()->r.raydir_y;
	}
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
