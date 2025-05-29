/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:43:25 by glabaden          #+#    #+#             */
/*   Updated: 2025/05/29 11:43:28 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_surrounded(char **map, int i, int j)
{
	if (i == 0 || (int)j >= (int)strlen(map[i - 1])
		|| map[i - 1][j] == ' ' || map[i - 1][j] == '\0')
		return (0);
	if (!map[i + 1] || (int)j >= (int)strlen(map[i + 1])
		|| map[i + 1][j] == ' ' || map[i + 1][j] == '\0')
		return (0);
	if (j == 0 || map[i][j - 1] == ' ' || map[i][j - 1] == '\0')
		return (0);
	if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
		return (0);
	return (1);
}

int	ismapvalid(void)
{
	int		i;
	int		j;
	char	**map;

	map = s()->map.data;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!is_surrounded(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(void)
{
	int		i;
	int		j;
	int		player_count;
	char	**map;

	map = s()->map.data;
	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\n')
				map[i][j] = '\0';
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
					map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			else if(map[i][j] != '0' && map[i][j] != '1' &&
					map[i][j] != ' ' && map[i][j] != '\0')
				return(write(2, "Charactere non autorise\n",24), 0);
			j++;
		}
		i++;
	}
	if (player_count != 1 || ismapvalid() != 1)
		return (0);
	return (1);
}
