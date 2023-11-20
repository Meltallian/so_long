/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ber_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:59:44 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/20 15:34:14 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_height(int i)
{
	char *line;
	int fd;

	fd = open("map.ber", O_RDONLY);
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
	fd = open("map.ber", O_RDONLY);
	return (i);
}

void	ft_free(char **map, int i)
{
	while(i >= 0)
	{
		free(map[i]);
		map[i] = NULL;
		i--;
	}
}

void	parse_ber_file(int fd, t_map *mapping)
{
	char	*line;
	int		i;

	i = 0;
	mapping->map = malloc((map_height(mapping->height) + 1)* sizeof(char *));
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		mapping->map[i] = line;
		if (mapping->map[i] == NULL)
		{
			ft_free(mapping->map, i);
			free(mapping->map);
			break ;
		}
		i++;
	}
	mapping->map[i] = 0;
}

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
