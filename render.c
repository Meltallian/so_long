/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:44:24 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/28 17:54:37 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_sprites(t_map *game)
{
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
	game->chara.found = 0;
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

void	render_map(t_map *game)
{
	int				i;
	int				j;
	unsigned char	tile;

	i = 0;
	j = 0;
	anim(game);
	while (game->map[i])
	{
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			tile = (unsigned char)game->map[i][j];
			mlx_put_image_to_window(game->mlx, game->win,
				game->sprite_mapping['0'].img, j * 64, i * 64);
			if (game->map[i][j] != 'P'/*  && game->map[i][j] != '1' */)
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->sprite_mapping[tile].img, j * 64, i * 64);
			}
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->sprite_mapping['P'].img, game->chara.x, game->chara.y);
}

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
