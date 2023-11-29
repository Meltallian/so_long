/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:34:22 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/29 17:02:41 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mapcpy_check(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->mapcpy[i])
	{
		while (game->mapcpy[i][j] && game->mapcpy[i][j] != '\n')
		{
			if (game->mapcpy[i][j] == 'C' || game->mapcpy[i][j] == 'E')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	enemy_check(int keycode, t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x / 64;
	y = game->chara.y / 64;
	if (keycode == KEY_A && (game->map[y][x - 1] == 'X'
		|| game->map[y][x - 1] == 'Y'))
		return (0);
	if (keycode == KEY_W && (game->map[y - 1][x] == 'X'
		|| game->map[y - 1][x] == 'Y'))
		return (0);
	if (keycode == KEY_D && (game->map[y][x + 1] == 'X'
		|| game->map[y][x + 1] == 'Y'))
		return (0);
	if (keycode == KEY_S && (game->map[y + 1][x] == 'X'
		|| game->map[y + 1][x] == 'Y'))
		return (0);
	return (1);
}

void	enemy_call(t_map *game)
{
	ft_printf("Error\nGreed is a bottomless pit which exhausts the person \
in an endless effort to satisfy the need without \
ever reaching satisfaction. - Erich Fromm\nYou may try again.");
	destroy(game);
}

void	enemy_hit(int keycode, t_map *game)
{
	if (keycode == KEY_A && enemy_check(KEY_A, game) == 0)
		enemy_call(game);
	if (keycode == KEY_W && enemy_check(KEY_W, game) == 0)
		enemy_call(game);
	if (keycode == KEY_D && enemy_check(KEY_D, game) == 0)
		enemy_call(game);
	if (keycode == KEY_S && enemy_check(KEY_S, game) == 0)
		enemy_call(game);
}
