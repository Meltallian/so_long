/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:45 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/21 17:58:45 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	character_pos(t_map *game)
{
	game->chara.a = 0;
	game->chara.b = 0;
	game->chara.found = 0;
	while (game->map[game->chara.a] && !game->chara.found)
	{
		while (game->map[game->chara.a][game->chara.b] &&
			 game->map[game->chara.a][game->chara.b] != '\n')
		{
			if (game->map[game->chara.a][game->chara.b] == 'P')
			{
				game->chara.found = 1;
				break;
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

void	load_sprites(t_map *game)
{
	game->sprite_mapping['P'].img = mlx_xpm_file_to_image(game->mlx, "images/kawai.xpm",
		&game->sprite_mapping['P'].width, &game->sprite_mapping['P'].height);
	game->sprite_mapping['C'].img = mlx_xpm_file_to_image(game->mlx, "images/candy_l.xpm",
		&game->sprite_mapping['C'].width, &game->sprite_mapping['C'].height);
	game->sprite_mapping['1'].img = mlx_xpm_file_to_image(game->mlx, "images/tree.xpm",
		&game->sprite_mapping['1'].width, &game->sprite_mapping['1'].height);
	game->sprite_mapping['0'].img = mlx_xpm_file_to_image(game->mlx, "images/ground.xpm",
		&game->sprite_mapping['0'].width, &game->sprite_mapping['0'].height);
	game->sprite_mapping['E'].img = mlx_xpm_file_to_image(game->mlx, "images/gate.xpm",
		&game->sprite_mapping['E'].width, &game->sprite_mapping['E'].height);
}

void	render_map(t_map *game)
{
	int				i;
	int				j;
	unsigned char	tile;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			tile = (unsigned char)game->map[i][j];
			mlx_put_image_to_window(game->mlx, game->win,
				game->sprite_mapping['0'].img, j * 64, i * 64);
			if (game->map[i][j] != 'P')
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

void	img_destr(t_map *map)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (map->sprite_mapping[i].img != NULL)
		{
			mlx_destroy_image(map->mlx, map->sprite_mapping[i].img);
			map->sprite_mapping[i].img = NULL;
		}
		i++;
	}
}

int	key_hook(int keycode, t_map *game)
{
	int tile_size;

	tile_size = 64;
	if (keycode == KEY_ESC)
		exit(0); // destroy window etc
	if (keycode == KEY_A)
		game->chara.x -= tile_size;
	if (keycode == KEY_W)
		game->chara.y -= tile_size;
	if (keycode == KEY_D)
		game->chara.x += tile_size;
	if (keycode == KEY_S)
		game->chara.y += tile_size;
	render_map(game);
	return (0);
}

int main()
{
	t_map	game;
	int		i;

	i = 0;
	while (i < 256)
		game.sprite_mapping[i++].img = NULL; //Necessaire pour pouvoir destroy chaque image apres.

	game.mlx = mlx_init();
	load_sprites(&game);

	parse_ber_file(&game);
	game.win = mlx_new_window(game.mlx, game.width, game.height*64, "PeepoPog");
	mlx_new_image(game.mlx, game.width, game.height*64);

	character_pos(&game);
	render_map(&game);

	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);

	img_destr(&game);
	i = 0;
	while (game.map[i])
	{
		free(game.map[i]);
		i++;
	}
	free(game.map);
	mlx_destroy_window(game.mlx, game.win);
	return 0;
}
