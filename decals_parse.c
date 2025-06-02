/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decals_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:57:01 by estegana          #+#    #+#             */
/*   Updated: 2025/05/28 11:57:04 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	set_text_path(int identifier, char *filename, t_config *conf)
{
	if (identifier == 2)
	{
		if (conf->decals.n.path)
			free(conf->decals.n.path);
		conf->decals.n.path = ft_strdup(filename);
	}
	else if (identifier == 3)
	{
		if (conf->decals.s.path)
			free(conf->decals.s.path);
		conf->decals.s.path = ft_strdup(filename);
	}
	else if (identifier == 4)
	{
		if (conf->decals.w.path)
			free(conf->decals.w.path);
		conf->decals.w.path = ft_strdup(filename);
	}
	else if (identifier == 5)
	{
		if (conf->decals.e.path)
			free(conf->decals.e.path);
		conf->decals.e.path = ft_strdup(filename);
	}
}

int	handle_files(char *line, t_config *conf, int identifier)
{
	int		fd;
	char	*filename;
	size_t	len;

	filename = line + 3;
	len = ft_strlen(filename);
	if (len > 0 && filename[len - 1] == '\n')
		filename[len - 1] = '\0';
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".xpm\0", 5))
		return (free_map(), free_decals(),
			write(2, "Files must be .xpm\n", 19), 0);
	while (*filename == ' ')
		filename++;
	if (open(filename, O_DIRECTORY) != -1)
		return (free_map(), free_decals(),
			write(2, "texture is a directory\n", 23), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free_map(), free_decals(),
			write(2, "a File can't open\n", 18), 0);
	set_text_path(identifier, filename, conf);
	return (close(fd), 1);
}

void	set_rgb_color(t_color *color, int i, int number)
{
	if (i == 0)
		color->r = number;
	else if (i == 1)
		color->g = number;
	else if (i == 2)
		color->b = number;
}

int	handle_rgb(int identifier, t_config *conf, char **rgb)
{
	int	i;
	int	number;

	i = 0;
	while (rgb[i])
	{
		number = ft_atoi(rgb[i]);
		if (number < 0 || number > 255)
			return (write(2, "Incorrect format for RGB\n", 25), 0);
		if (identifier == 6)
			set_rgb_color(&conf->decals.floor_color, i, number);
		else if (identifier == 7)
			set_rgb_color(&conf->decals.ceiling_color, i, number);
		i++;
	}
	if (i != 3)
		return (write(2, "Incorrect format for RGB\n", 25), 0);
	return (1);
}

int	handle_decals(char *filename, t_config *conf)
{
	char	*get_nextline;
	int		identifier;
	int		fd_decals;

	fd_decals = open(filename, O_RDONLY);
	if (fd_decals < 0)
		return (0);
	get_nextline = get_next_line(fd_decals);
	while (get_nextline)
	{
		identifier = find_identifier(get_nextline);
		if (identifier)
		{
			if (!parse_identifier(get_nextline, identifier, conf))
				return (free_gnl(get_nextline, fd_decals), 0);
		}
		else
			free(get_nextline);
		get_nextline = get_next_line(fd_decals);
	}
	free(get_nextline);
	close(fd_decals);
	return (1);
}
