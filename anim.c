/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:13:43 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/28 18:02:54 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	anim_utils(t_map *game, char c, int i, int j)
{
	if (c == 'R')
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprite_mapping['R'].img, j * 64, i * 64);
		game->map[i][j] = 'R';
	}
	if (c == 'L')
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprite_mapping['L'].img, j * 64, i * 64);
		game->map[i][j] = 'L';
	}
	if (c == '1')
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprite_mapping['1'].img, j * 64, i * 64);
		game->map[i][j] = '1';
	}
	return (0);
}

void	anim(t_map *game)
{
	int				i;
	int				j;
	static int		k = 0;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if (game->map[i][j] == '1' && k % 3 == 1)
				anim_utils(game, 'R', i, j);
			else if (game->map[i][j] == 'R' || game->map[i][j] == 'L')
			{
				anim_utils(game, '1', i, j);
				k++;
			}
			else if (game->map[i][j] == '1' && k % 3 == 0)
				anim_utils(game, 'L', i, j);
			j++;
		}
		j = 0;
		i++;
	}
	k += 1;
}
