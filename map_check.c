#include "cub3d.h"

int	is_valid_adjacent(char c)
{
	return (c == '1' || c == ' ');
}

int	check_surroundings(char **map, int i, int j)
{
	int	di[4] = {-1, 0, 0, 1};
	int	dj[4] = {0, -1, 1, 0};
	int	ni;
	int	nj;
	int	k;

    k = 0;
	while (k != 4)
	{
		ni = i + di[k];
		nj = j + dj[k];
		if (ni >= 0 && map[ni] && nj >= 0 && nj < (int)strlen(map[ni]))
		{
			char adj = map[ni][nj];
			if (!is_valid_adjacent(adj))
				return (0);
		}
		k++;
	}
	return (1);
}

int	isMapValid(void)
{
	char	**map = s()->map.data;
	int		i = 0, j;
	int		rows, cols;

	rows = 0;
	while (map[rows])
		rows++;
	cols = s()->map.columns;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{

			if (i == 0 || i == rows - 1)
			{
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (2);
			}
			if ((j == 0 || j == (int)ft_strlen(map[i]) - 1) && map[i][j] != ' ' && map[i][j] != '1')
				return (2);
			if (map[i][j] == ' ')
			{
				if (!check_surroundings(map, i, j))
					return (3);
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
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1 ||  isMapValid() != 1)
		return (0);
	return (1);
}