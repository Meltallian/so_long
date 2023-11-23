/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:45 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/23 17:23:22 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	mlx_destroy_window(game->mlx, game->win);
	exit (0);
	return (0);
}

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


int	candy(t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x/64;
	y = game->chara.y/64;
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

int	map_similar(t_map *game)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if (game->mapcpy[i][j] != game->map[i][j])
			{
				if (game->mapcpy[i][j] != 'P')
					return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	valid_path(t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x / 64;
	y = game->chara.y / 64;
	while (game->mapcpy[y][x + 1] == 0)
	{
		game->mapcpy[y][x] = 'P';
		x += 1;
	}
	while (game->mapcpy[y][x - 1])
	{
		game->mapcpy[y][x] = 'P';
		x -= 1;
	}
	while (game->mapcpy[y + 1][x])
	{
		game->mapcpy[y][x] = 'P';
		y += 1;
	}
	while (game->mapcpy[y - 1][x])
	{
		game->mapcpy[y][x] = 'P';
		y -= 1;
	}
	return (0);
}

int	wallhit(int direction, t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x/64;
	y = game->chara.y/64;
	if (direction == KEY_A && game->map[y][x - 1] == '1')
		return (1);
	if (direction == KEY_W && game->map[y - 1][x] == '1')
		return (1);
	if (direction == KEY_D && game->map[y][x + 1] == '1')
		return (1);
	if (direction == KEY_S && game->map[y + 1][x] == '1')
		return (1);
	return (0);
}

void	exitdoor(t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x/64;
	y = game->chara.y/64;
	if (game->map[y][x] == 'E' && candy(game) == 1)
		destroy(game);
}

int	key_hook(int keycode, t_map *game)
{
	static int	display = 0;

	if (keycode == KEY_ESC)
		destroy(game);
	if (keycode == KEY_A && wallhit(KEY_A ,game) == 0)
		game->chara.x -= 64;
	if (keycode == KEY_W && wallhit(KEY_W ,game) == 0)
		game->chara.y -= 64;
	if (keycode == KEY_D && wallhit(KEY_D ,game) == 0)
		game->chara.x += 64;
	if (keycode == KEY_S && wallhit(KEY_S ,game) == 0)
		game->chara.y += 64;
	display++;
	ft_printf("The current number of movements is: %d\n", display);
	candy(game);
	exitdoor(game);
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
	parse_ber_filecpy(&game);
	game.win = mlx_new_window(game.mlx, game.width, game.height*64, "PeepoPog");
	mlx_new_image(game.mlx, game.width, game.height*64);


	candynum(&game);
	character_pos(&game);
	valid_path(&game);

	render_map(&game);

	mlx_hook(game.win, 17, 0, destroy, &game);
	mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
//	mlx_key_hook(game.win, key_hook, &game);

	mlx_loop(game.mlx);

	destroy(&game);
	return 0;
}
