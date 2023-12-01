/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:45 by jbidaux           #+#    #+#             */
/*   Updated: 2023/12/01 12:30:38 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber(t_map *game)
{
	static char	*ber_ext = ".ber";
	size_t		ber_len;
	size_t		filename_len;

	filename_len = ft_strlen(game->ber);
	ber_len = ft_strlen(ber_ext);
	if (filename_len >= ber_len
		&& ft_strncmp(game->ber + filename_len
			- ber_len, ber_ext, ber_len) == 0)
		return (1);
	else
		return (0);
}

int	main(int ac, char **av)
{
	t_map	game;

	if (ac != 2)
	{
		ft_printf("Wrong number of arguments");
		return (0);
	}
	game.ber = av[1];
	init(&game);
	destroy(&game);
	return (0);
}

/*
int	main(void)
{
	t_map	game;

	game.ber = "map.ber";
	if (check_ber(&game) == 0)
	{
		ft_printf("Error\nIt ain't a '.ber' file mon reuf.");
		return (0);
	}

	init(&game);
	destroy(&game);
	return (0);
} */
