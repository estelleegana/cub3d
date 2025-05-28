/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:50:30 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 11:50:31 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_tex(void)
{
	int	i;

	s()->t = malloc(sizeof(t_texture) * 4);
	s()->t[0].path = s()->decals.n.path;
	s()->t[1].path = s()->decals.s.path;
	s()->t[2].path = s()->decals.e.path;
	s()->t[3].path = s()->decals.w.path;
	i = 0;
	while (i < 4)
	{
		s()->t[i].img = mlx_xpm_file_to_image(s()->mlx,
		s()->t[i].path, &s()->t[i].w, &s()->t[i].h);
		if (!s()->t[i].img)
			return ;
		s()->t[i].addr = mlx_get_data_addr(s()->t[i].img,
		&s()->t[i].bpp, &s()->t[i].line_len, &s()->t[i].endian);
		if (!s()->t[i].addr)
			return ;
		i++;
	}
}

void init_player(void)
{
	char c;
	int y;
	int found;

	y = 0;
	found = 0;
	while (y < s()->map.line && !found)
	{
		int x = 0;
		while (x < s()->map.columns && s()->map.data[y][x] && !found)
		{
			c = s()->map.data[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				s()->p.x = x;
				s()->p.y = y;
				if (c == 'N')
				{
					s()->p.dir_x = 0;
					s()->p.dir_y = -1;
					s()->p.plane_x = 0.66;
					s()->p.plane_y = 0.0;
				}
				if (c == 'S')
				{
					s()->p.dir_x = 0;
					s()->p.dir_y = 1;
					s()->p.plane_x = -0.66;
					s()->p.plane_y = 0.0;
				}
				if (c == 'E')
				{
					s()->p.dir_x = 1;
					s()->p.dir_y = 0;
					s()->p.plane_x = 0.0;
					s()->p.plane_y = 0.66;
				}
				if (c == 'W')
				{
					s()->p.dir_x = -1;
					s()->p.dir_y = 0;
					s()->p.plane_x = 0.0;
					s()->p.plane_y = -0.66;
				}
				found = 1;
			}
			x++;
		}
		y++;
	}
	return;
}

void	init_game(void)
{
	s()->mlx = mlx_init();
	if (s()->mlx == NULL)
		return ;
	s()->win = mlx_new_window(s()->mlx, WIDTH, HEIGHT, NAME);
	if (s()->win == NULL)
		return ;
	init_tex();
	s()->img = mlx_new_image(s()->mlx, WIDTH, HEIGHT);
	s()->pixel_data
	= mlx_get_data_addr(s()->img,
	&s()->bpp,
	&s()->size_line, &s()->endian);
	mlx_put_image_to_window(s()->mlx, s()->win, s()->img, 0, 0);
	mlx_hook(s()->win, 17, 0L, close_window_cross, NULL);
	mlx_hook(s()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(s()->win, 3, 1L << 1, key_release, NULL);
	mlx_loop_hook(s()->mlx, game_loop, NULL);
	mlx_loop(s()->mlx);
}
