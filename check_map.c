/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:44:45 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/28 14:45:04 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_1_border(t_map *game)
{
	int	j;
	int	height;
	int	width;

	height = game->height - 1;
	width = game->width / 64;
	j = 0;
	while (game->map[0][j] && game->map[0][j] != '\n')
	{
		if (game->map[0][j] != '1' || game->map[height][j] != '1')
			return (0);
		j++;
	}
	j = 0;
	while (j <= height)
	{
		if (game->map[j][0] != '1' || game->map[j][width - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	is_rekt(t_map *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (game->map[0][i] != '\n' && game->map[0][i])
		i++;
	while (game->map[j])
	{
		while (game->map[j][k] != '\n' && game->map[j][k])
			k++;
		if (i != k)
			return (0);
		j++;
	}
	return (1);
}

void	check_comps(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->coor.c = 0;
	game->coor.e = 0;
	game->coor.p = 0;
	while (game->map[i])
	{
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if (game->map[i][j] == 'C')
				game->coor.c++;
			if (game->map[i][j] == 'E')
				game->coor.e++;
			if (game->map[i][j] == 'P')
				game->coor.p++;
			j++;
		}
		j = 0;
		i++;
	}
}

int	valid_comps(t_map *game)
{
	check_comps(game);
	if (game->coor.c < 1
		|| game->coor.e != 1
		|| game->coor.p != 1)
		return (0);
	return (1);
}

void	valid_path(t_map *game)
{
	if (valid_comps(game) == 0)
	{
		ft_printf("Mon reuf, t'as mal géré les composants.");
		destroy(game);
	}
	game->mapcpy[game->chara.y / 64][game->chara.x / 64] = '0';
	flood_pogging(game, game->chara.x / 64, game->chara.y / 64);
	if (mapcpy_check(game) == 0)
	{
		ft_printf("La map est pas realisable mono reuf.");
		destroy(game);
	}
	if (is_rekt(game) == 0)
	{
		ft_printf("Bruh, la map est pas rectangle.");
		destroy(game);
	}
	if (check_1_border(game) == 0)
	{
		ft_printf("Bruh, where do be them 1s.");
		destroy(game);
	}
}
