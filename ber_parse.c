/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ber_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:59:44 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/28 15:10:31 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_height(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
		return (0);
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
	mapping->height = map_height();
	mapping->map = malloc((mapping->height + 1) * sizeof(char *));
	if (!mapping->map)
		return ;
	fd = open("map.ber", O_RDONLY);
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
	fd = open("map.ber", O_RDONLY);
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

/*
int main()
{
	t_map	mapping;
	int		fd;
	int		i;

	mapping.map = 0;
	i = 0;
	fd = open("map.ber", O_RDONLY);
	parse_ber_file(fd, &mapping);
	close(fd);
	while (mapping.map[i])
	{
		printf("%s", mapping.map[i]);
		free(mapping.map[i]);
		i++;
	}
	free(mapping.map);
	return 0;
}
 */