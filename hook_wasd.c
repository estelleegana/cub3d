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
	double	margin;

	margin = 0.01;
	new_x = s()->p.x + s()->p.dir_x * SPEED;
	new_y = s()->p.y + s()->p.dir_y * SPEED;
	if (s()->map.data[(int)(s()->p.y)][(int)(new_x + margin * s()->p.dir_x)]
		!= '1')
		s()->p.x = new_x;
	if (s()->map.data[(int)(new_y + margin * s()->p.dir_y)][(int)(s()->p.x)]
		!= '1')
		s()->p.y = new_y;
}

void	key_s(void)
{
	double	new_x;
	double	new_y;
	double	margin;

	margin = 0.01;
	new_x = s()->p.x - s()->p.dir_x * SPEED;
	new_y = s()->p.y - s()->p.dir_y * SPEED;
	if (s()->map.data[(int)(s()->p.y)][(int)(new_x - margin * s()->p.dir_x)]
		!= '1')
		s()->p.x = new_x;
	if (s()->map.data[(int)(new_y - margin * s()->p.dir_y)][(int)(s()->p.x)]
		!= '1')
		s()->p.y = new_y;
}

void	key_a(void)
{
	double	newplane_x;
	double	newplane_y;

	newplane_x = s()->p.x - s()->p.plane_x * SPEED;
	newplane_y = s()->p.y - s()->p.plane_y * SPEED;
	if (s()->map.data[(int)s()->p.y][(int)newplane_x] != '1')
		s()->p.x = newplane_x;
	if (s()->map.data[(int)newplane_y][(int)s()->p.x] != '1')
		s()->p.y = newplane_y;
}

void	key_d(void)
{
	double	newplane_x;
	double	newplane_y;

	newplane_x = s()->p.x + s()->p.plane_x * SPEED;
	newplane_y = s()->p.y + s()->p.plane_y * SPEED;
	if (s()->map.data[(int)s()->p.y][(int)newplane_x] != '1')
		s()->p.x = newplane_x;
	if (s()->map.data[(int)newplane_y][(int)s()->p.x] != '1')
		s()->p.y = newplane_y;
}
