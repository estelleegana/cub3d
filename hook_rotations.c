/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_rotations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:01:00 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 12:01:01 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//formules des rotations 2D:
//x' = x * cos(θ) - y * sin(θ)
//y' = x * sin(θ) + y * cos(θ)
void	key_left(void)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = s()->p.dir_x;
	old_plane_x = s()->p.plane_x;
	s()->p.dir_x = s()->p.dir_x * cos(-ROT_SPEED)
	- s()->p.dir_y * sin(-ROT_SPEED);
	s()->p.dir_y = old_dir_x * sin(-ROT_SPEED)
	+ s()->p.dir_y * cos(-ROT_SPEED);
	s()->p.plane_x = s()->p.plane_x * cos(-ROT_SPEED)
	- s()->p.plane_y * sin(-ROT_SPEED);
	s()->p.plane_y = old_plane_x * sin(-ROT_SPEED)
	+ s()->p.plane_y * cos(-ROT_SPEED);
}

void	key_right(void)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = s()->p.dir_x;
	old_plane_x = s()->p.plane_x;
	s()->p.dir_x = s()->p.dir_x * cos(ROT_SPEED)
	- s()->p.dir_y * sin(ROT_SPEED);
	s()->p.dir_y = old_dir_x * sin(ROT_SPEED)
	+ s()->p.dir_y * cos(ROT_SPEED);
	s()->p.plane_x = s()->p.plane_x * cos(ROT_SPEED)
	- s()->p.plane_y * sin(ROT_SPEED);
	s()->p.plane_y = old_plane_x * sin(ROT_SPEED)
	+ s()->p.plane_y * cos(ROT_SPEED);
}
