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
