/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_wasd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:56:35 by estegana          #+#    #+#             */
/*   Updated: 2025/05/27 17:56:38 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_w(void)
{
	double	new_x;
	double	new_y;

	new_x = s()->p.X + s()->p.dir_x * speed;
	new_y = s()->p.Y + s()->p.dir_y * speed;
	if (s()->map.data[(int)s()->p.Y][(int)new_x] != '1')
		s()->p.X = new_x;
	if (s()->map.data[(int)new_y][(int)s()->p.X] != '1')
		s()->p.Y = new_y;
}

void	key_s(void)
{
	double	new_x;
	double	new_y;

	new_x = s()->p.X - s()->p.dir_x * speed;
	new_y = s()->p.Y - s()->p.dir_y * speed;
	if (s()->map.data[(int)s()->p.Y][(int)new_x] != '1')
		s()->p.X = new_x;
	if (s()->map.data[(int)new_y][(int)s()->p.X] != '1')
		s()->p.Y = new_y;
}

void	key_a(void)
{
	double	newplane_x;
	double	newplane_y;

	newplane_x = s()->p.X - s()->p.plane_x * speed;
	newplane_y = s()->p.Y - s()->p.plane_y * speed;
	if (s()->map.data[(int)s()->p.Y][(int)newplane_x] != '1')
		s()->p.X = newplane_x;
	if (s()->map.data[(int)newplane_y][(int)s()->p.X] != '1')
		s()->p.Y = newplane_y;
}

void	key_d(void)
{
	double	newplane_x;
	double	newplane_y;

	newplane_x = s()->p.X + s()->p.plane_x * speed;
	newplane_y = s()->p.Y + s()->p.plane_y * speed;
	if (s()->map.data[(int)s()->p.Y][(int)newplane_x] != '1')
		s()->p.X = newplane_x;
	if (s()->map.data[(int)newplane_y][(int)s()->p.X] != '1')
		s()->p.Y = newplane_y;
}
