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

void	init_pos_surroundings(int *di, int *dj)
{
	di[0] = -1;
	di[1] = 0;
	di[2] = 0;
	di[3] = 1;
	dj[0] = 0;
	dj[1] = -1;
	dj[2] = 1;
	dj[3] = 0;
}

int	check_surroundings(char **map, int i, int j)
{
	int	di[4];
	int	dj[4];
	int	ni;
	int	nj;
	int	k;

	k = 0;
	init_pos_surroundings(di, dj);
	while (k != 4)
	{
		ni = i + di[k];
		nj = j + dj[k];
		if (ni >= 0 && map[ni] && nj >= 0 && nj < (int)strlen(map[ni]))
		{
			if (map[ni][nj] != '1' || map[ni][nj] != ' ')
				return (0);
		}
		k++;
	}
	return (1);
}

int	multi_check(char **map, int i, int j, int rows)
{
	if (i == 0 || i == rows - 1)
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
	}
	if ((j == 0 || j == (int)ft_strlen(map[i]) - 1)
		&& map[i][j] != ' ' && map[i][j] != '1')
		return (0);
	if (map[i][j] == ' ')
	{
		if (!check_surroundings(map, i, j))
			return (0);
	}
	return (1);
}

int	ismapvalid(void)
{
	char	**map;
	int		i;
	int		j;
	int		rows;

	map = s()->map.data;
	rows = 0;
	while (map[rows])
		rows++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!multi_check(map, i, j, rows))
				return (0);
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
			j++;
		}
		i++;
	}
	if (player_count != 1 || ismapvalid() != 1)
		return (0);
	return (1);
}
