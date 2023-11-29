/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ber_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:59:44 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/29 17:39:45 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_height(t_map *game)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(game->ber, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nLa map, please.");
		exit (0);
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free (line);
		i++;
	}
	close(fd);
	return (i);
}

void	parse_ber_file(t_map *mapping)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	mapping->height = map_height(mapping);
	mapping->map = malloc((mapping->height + 1) * sizeof(char *));
	if (!mapping->map)
		return ;
	fd = open(mapping->ber, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		mapping->map[i] = line;
		i++;
	}
	mapping->map[i] = 0;
	mapping->width = ft_strlen(mapping->map[0]) * 64 - 64;
	close(fd);
}

void	parse_ber_filecpy(t_map *mapping)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	mapping->mapcpy = malloc((mapping->height + 1) * sizeof(char *));
	if (!mapping->mapcpy)
		return ;
	fd = open(mapping->ber, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		mapping->mapcpy[i] = line;
		i++;
	}
	mapping->mapcpy[i] = 0;
	close(fd);
}

void	flood_pogging(t_map *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height)
		return ;
	if (game->mapcpy[y][x] != '0' &&
		game->mapcpy[y][x] != 'C' &&
		game->mapcpy[y][x] != 'E')
		return ;
	game->mapcpy[y][x] = 'P';
	flood_pogging(game, x + 1, y);
	flood_pogging(game, x - 1, y);
	flood_pogging(game, x, y + 1);
	flood_pogging(game, x, y - 1);
}
