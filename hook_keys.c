/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:56:03 by estegana          #+#    #+#             */
/*   Updated: 2025/05/27 17:56:04 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window_echap(void)
{
	mlx_destroy_window(s()->mlx, s()->win);
	mlx_destroy_display(s()->mlx);
	free(s()->mlx);
	exit(0);
	return (0);
}

int	close_window_cross(void)
{
	mlx_destroy_window(s()->mlx, s()->win);
	mlx_destroy_display(s()->mlx);
	free(s()->mlx);
	exit(0);
}

int	key_press(int touche)
{
	if (touche == W)
		s()->k.w = 1;
	else if (touche == S)
		s()->k.s = 1;
	else if (touche == D)
		s()->k.d = 1;
	else if (touche == A)
		s()->k.a = 1;
	else if (touche == RIGHT)
		s()->k.right = 1;
	else if (touche == LEFT)
		s()->k.left = 1;
	else if (touche == ECHAP)
		close_window_echap();
	return (0);
}

int	key_release(int touche)
{
	if (touche == W)
		s()->k.w = 0;
	else if (touche == S)
		s()->k.s = 0;
	else if (touche == D)
		s()->k.d = 0;
	else if (touche == A)
		s()->k.a = 0;
	else if (touche == RIGHT)
		s()->k.right = 0;
	else if (touche == LEFT)
		s()->k.left = 0;
	return (0);
}

int	game_loop(void)
{
	if (s()->k.w)
		key_w();
	if (s()->k.s)
		key_s();
	if (s()->k.a)
		key_a();
	if (s()->k.d)
		key_d();
	if (s()->k.left)
		key_left();
	if (s()->k.right)
		key_right();
	raycasting(s());
	return (0);
}
