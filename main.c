/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:56:53 by estegana          #+#    #+#             */
/*   Updated: 2025/05/27 17:56:57 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (write(2, "Error // Wrong number of arguments\n", 35), 1);
	if (!parse_cub(argv[1]))
		return (write(2, "Error // Invalid .cub file\n", 27), 1);
	init_player();
	init_game();
	free_map();
	free_textures();
	return (0);
}
