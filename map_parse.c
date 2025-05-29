/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:19:46 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 12:19:47 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_a_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' || line[i] != '0')
			return (1);
		i++;
	}
	return (0);
}

int	fill_map(char *filename)
{
	int		fd;
	char	*get_nline;
	int		start_map;

	start_map = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	get_nline = get_next_line(fd);
	while (get_nline)
	{
		if (!find_identifier(get_nline) && is_a_map_line(get_nline))
		{
			s()->map.data[start_map] = ft_strdup(get_nline);
			if (!s()->map.data[start_map])
				return (write(2, "Error // Memory allocation failed\n", 35), 0);
			if (s()->map.columns < (int)ft_strlen(s()->map.data[start_map]))
				s()->map.columns = (int)ft_strlen(s()->map.data[start_map]);
			start_map++;
		}
		free(get_nline);
		get_nline = get_next_line(fd);
	}
	close(fd);
	return (start_map);
}

int	ft_count_line_column(char *filename)
{
	int		fd;
	char	*get_nline;
	int		start_map;

	start_map = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	get_nline = get_next_line(fd);
	while (get_nline)
	{
		if (find_identifier(get_nline))
			start_map++;
		else
		{
			if (is_a_map_line(get_nline))
				s()->map.line++;
		}
		free(get_nline);
		get_nline = get_next_line(fd);
	}
	close(fd);
	return (start_map);
}

int	handle_map(char *filename)
{
	int	start_map;

	start_map = ft_count_line_column(filename);
	if (start_map == 0)
		return (write(2, "Error // No map found\n", 22), 0);
	if (start_map > 6)
		return (write(2, "Error // Trop d'element dans le header\n", 39), 0);
	s()->map.data = malloc(sizeof(char *) * (s()->map.line + 1));
	if (!s()->map.data)
		return (write(2, "Error // Memory allocation failed\n", 35), 0);
	s()->map.data[s()->map.line] = NULL;
	s()->map.columns = 0;
	fill_map(filename);
	if (!check_map())
		return (free_map(), 0);
	return (1);
}
