/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:45 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/28 17:10:07 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
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
 */
int	main(void)
{
	t_map	game;

	game.ber = "map.ber";
	init(&game);
	destroy(&game);
	return (0);
}