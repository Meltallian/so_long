/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cand_destr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:38:48 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/29 17:49:26 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	i = 0;
	while (game->mapcpy[i])
	{
		free(game->mapcpy[i]);
		i++;
	}
	free(game->mapcpy);
}

int	destroy(t_map *game)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (game->sprite_mapping[i].img != NULL)
		{
			mlx_destroy_image(game->mlx, game->sprite_mapping[i].img);
			game->sprite_mapping[i].img = NULL;
		}
		i++;
	}
	i = 0;
	free_map(game);
	mlx_destroy_window(game->mlx, game->win);
	exit (0);
	return (0);
}

int	candy(t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x / 64;
	y = game->chara.y / 64;
	if (game->map[y][x] == 'C')
	{
		game->map[y][x] = '0';
		game->candcount--;
	}
	if (game->candcount == 0)
		return (1);
	return (0);
}

void	candynum(t_map *game)
{
	int	i;
	int	j;
	int	candycount;

	i = 0;
	j = 0;
	candycount = 0;
	while (game->map[i])
	{
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if (game->map[i][j] == 'C')
			candycount++;
			j++;
		}
		j = 0;
		i++;
	}
	game->candcount = candycount;
}

void	exitdoor(t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x / 64;
	y = game->chara.y / 64;
	if (game->map[y][x] == 'E' && candy(game) == 1)
	{
		ft_printf("Congratulations, you have proven yourself worthy.");
		destroy(game);
	}
}
