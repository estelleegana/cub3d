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
	int			i;
	t_config	*config;

	config = s();
	s()->t = malloc(sizeof(t_texture) * 4);
	s()->t[0].path = s()->decals.n.path;
	s()->t[1].path = s()->decals.s.path;
	s()->t[2].path = s()->decals.e.path;
	s()->t[3].path = s()->decals.w.path;
	i = 0;
	while (i < 4)
	{
		config->t[i].img = mlx_xpm_file_to_image(config->mlx,
				config->t[i].path, &config->t[i].w, &config->t[i].h);
		if (!s()->t[i].img)
			return ;
		config->t[i].addr = mlx_get_data_addr(config->t[i].img,
				&config->t[i].bpp, &config->t[i].line_len, &s()->t[i].endian);
		if (!s()->t[i].addr)
			return ;
		i++;
	}
}

void	set_player_pos(double dir_x, double dir_y,
	double plane_x, double plane_y)
{
	s()->p.dir_x = dir_x;
	s()->p.dir_y = dir_y;
	s()->p.plane_x = plane_x;
	s()->p.plane_y = plane_y;
}

void	init_player_pos(char c, int x, int y)
{
	s()->p.x = x + 0.5;
	s()->p.y = y + 0.5;
	if (c == 'N')
		set_player_pos(0, -1, 0.66, 0.0);
	if (c == 'S')
		set_player_pos(0, 1, -0.66, 0.0);
	if (c == 'E')
		set_player_pos(1, 0, 0.0, 0.66);
	if (c == 'W')
		set_player_pos(-1, 0, 0.0, -0.66);
}

void	init_player(void)
{
	char	c;
	int		y;
	int		found;
	int		x;

	y = 0;
	found = 0;
	while (y < s()->map.line && !found)
	{
		x = 0;
		while (x < s()->map.columns && s()->map.data[y][x] && !found)
		{
			c = s()->map.data[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				init_player_pos(c, x, y);
				found = 1;
			}
			x++;
		}
		y++;
	}
	return ;
}

void	init_game(void)
{
	t_config	*config;

	config = s();
	config->mlx = mlx_init();
	if (config->mlx == NULL)
	{
		free_map();
		exit(1);
	}
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, NAME);
	if (config->win == NULL)
	{
		free_map();
		exit(1);
	}
	init_tex();
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	config->pixel_data = mlx_get_data_addr(config->img, &config->bpp,
			&config->size_line, &config->endian);
	mlx_put_image_to_window(s()->mlx, s()->win, s()->img, 0, 0);
	mlx_hook(s()->win, 17, 0L, close_window_cross, NULL);
	mlx_hook(s()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(s()->win, 3, 1L << 1, key_release, NULL);
	mlx_loop_hook(s()->mlx, game_loop, NULL);
	mlx_loop(s()->mlx);
}
