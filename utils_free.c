/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:55:03 by estegana          #+#    #+#             */
/*   Updated: 2025/05/27 17:55:04 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(void)
{
	int	i;

	i = 0;
	if (!s()->map.data)
		return ;
	while (s()->map.data[i])
	{
		free(s()->map.data[i]);
		i++;
	}
	free(s()->map.data);
}

void	free_textures(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (s()->t[i].img)
			mlx_destroy_image(s()->mlx, s()->t[i].img);
		i++;
	}
	mlx_destroy_image(s()->mlx, s()->img);
	free(s()->decals.n.path);
	free(s()->decals.s.path);
	free(s()->decals.w.path);
	free(s()->decals.e.path);
}
