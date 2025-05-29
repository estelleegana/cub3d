/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:20:14 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 12:20:15 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

int	parse_identifier(char *line, int identifier, t_config *conf)
{
	char	**rgb;
	int		i;

	i = 3;
	if (identifier <= 5 && identifier >= 2)
	{
		if (!handle_files(line, conf, identifier))
			return (0);
	}
	else if (identifier == 6 || identifier == 7)
	{
		while (line[i])
		{
			if (!ft_isdigit(line[i]) && line[i] != ','
				&& line[i] != '\0' && line[i] != '\n')
				return (free_map(), free_decals(), 0);
			i++;
		}
		rgb = ft_split(line + 2, ',');
		i = 0;
		if (!handle_rgb(identifier, conf, rgb))
			return (free_rgb(rgb), free_map(), free_decals(), 0);
		free_rgb(rgb);
	}
	return (free(line), 1);
}

int	find_identifier(char *line)
{
	if (ft_strlen(line) > 2)
	{
		if (line[0] == 'R' && line[1] == ' ')
			return (1);
		else if (line[0] == 'N' && line[1] == 'O')
			return (2);
		else if (line[0] == 'S' && line[1] == 'O')
			return (3);
		else if (line[0] == 'W' && line[1] == 'E')
			return (4);
		else if (line[0] == 'E' && line[1] == 'A')
			return (5);
		else if (line[0] == 'F')
			return (6);
		else if (line[0] == 'C')
			return (7);
	}
	return (0);
}

int	parse_cub(char *filename)
{
	t_config	*conf;

	conf = s();
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub\0", 5))
		return (0);
	if (!handle_map(filename))
		return (0);
	if (!handle_decals(filename, conf))
		return (0);
	if (!conf->decals.n.path || !conf->decals.s.path
		|| !conf->decals.w.path || !conf->decals.e.path)
	{
		write(2, "Error // Missing texture identifier\n", 36);
		free_map();
		free_decals();
		return (0);
	}
	return (1);
}
