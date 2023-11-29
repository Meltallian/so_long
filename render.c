/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:44:24 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/29 17:32:11 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sprites_utils(t_map *game)
{
	game->sprite_mapping['X'].img = mlx_xpm_file_to_image(game->mlx,
			"images/enemy.xpm", &game->sprite_mapping['X'].width,
			&game->sprite_mapping['X'].height);
	game->sprite_mapping['Y'].img = mlx_xpm_file_to_image(game->mlx,
			"images/enemy2.xpm", &game->sprite_mapping['Y'].width,
			&game->sprite_mapping['Y'].height);
	game->chara.found = 0;
}

void	load_sprites(t_map *game)
{
	sprites_utils(game);
	game->sprite_mapping['P'].img = mlx_xpm_file_to_image(game->mlx,
			"images/kawai.xpm", &game->sprite_mapping['P'].width,
			&game->sprite_mapping['P'].height);
	game->sprite_mapping['C'].img = mlx_xpm_file_to_image(game->mlx,
			"images/candy_l.xpm", &game->sprite_mapping['C'].width,
			&game->sprite_mapping['C'].height);
	game->sprite_mapping['1'].img = mlx_xpm_file_to_image(game->mlx,
			"images/tree.xpm", &game->sprite_mapping['1'].width,
			&game->sprite_mapping['1'].height);
	game->sprite_mapping['0'].img = mlx_xpm_file_to_image(game->mlx,
			"images/ground.xpm", &game->sprite_mapping['0'].width,
			&game->sprite_mapping['0'].height);
	game->sprite_mapping['E'].img = mlx_xpm_file_to_image(game->mlx,
			"images/gate.xpm", &game->sprite_mapping['E'].width,
			&game->sprite_mapping['E'].height);
	game->sprite_mapping['L'].img = mlx_xpm_file_to_image(game->mlx,
			"images/lefttree.xpm", &game->sprite_mapping['L'].width,
			&game->sprite_mapping['L'].height);
	game->sprite_mapping['R'].img = mlx_xpm_file_to_image(game->mlx,
			"images/righttree.xpm", &game->sprite_mapping['R'].width,
			&game->sprite_mapping['R'].height);
}

void	character_pos(t_map *game)
{
	game->chara.a = 0;
	game->chara.b = 0;
	while (game->map[game->chara.a] && !game->chara.found)
	{
		while (game->map[game->chara.a][game->chara.b] &&
		game->map[game->chara.a][game->chara.b] != '\n')
		{
			if (game->map[game->chara.a][game->chara.b] == 'P')
			{
				game->chara.found = 1;
				break ;
			}
			game->chara.b++;
		}
		if (!game->chara.found)
		{
			game->chara.a++;
			game->chara.b = 0;
		}
	}
	if (game->chara.found)
	{
		game->chara.x = game->chara.b * 64;
		game->chara.y = game->chara.a * 64;
	}
}

void	render_utils(t_map *game, int j, int i, unsigned char tile)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->sprite_mapping[tile].img, j * 64, i * 64);
}

void	render_map(t_map *game)
{
	int				i;
	int				j;
	unsigned char	tile;

	i = 0;
	j = 0;
	tree_anim(game);
	enemy_anim(game);
	while (game->map[i])
	{
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			tile = (unsigned char)game->map[i][j];
			mlx_put_image_to_window(game->mlx, game->win,
				game->sprite_mapping['0'].img, j * 64, i * 64);
			if (game->map[i][j] != 'P')
				render_utils(game, j, i, tile);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->sprite_mapping['P'].img, game->chara.x, game->chara.y);
}
