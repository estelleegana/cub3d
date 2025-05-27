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
	s()->p.dir_x = s()->p.dir_x * cos(-rot_speed) - s()->p.dir_y * sin(-rot_speed);
	s()->p.dir_y = old_dir_x * sin(-rot_speed) + s()->p.dir_y * cos(-rot_speed);
	s()->p.plane_x = s()->p.plane_x * cos(-rot_speed) - s()->p.plane_y * sin(-rot_speed);
	s()->p.plane_y = old_plane_x * sin(-rot_speed) + s()->p.plane_y * cos(-rot_speed);
}

void	key_right(void)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = s()->p.dir_x;
	old_plane_x = s()->p.plane_x;
	s()->p.dir_x = s()->p.dir_x * cos(rot_speed) - s()->p.dir_y * sin(rot_speed);
	s()->p.dir_y = old_dir_x * sin(rot_speed) + s()->p.dir_y * cos(rot_speed);
	s()->p.plane_x = s()->p.plane_x * cos(rot_speed) - s()->p.plane_y * sin(rot_speed);
	s()->p.plane_y = old_plane_x * sin(rot_speed) + s()->p.plane_y * cos(rot_speed);
}
