/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:45:19 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/28 15:05:12 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	wallhit(int direction, t_map *game)
{
	int	x;
	int	y;

	x = game->chara.x / 64;
	y = game->chara.y / 64;
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

int	key_dep(int keycode, t_map *game)
{
	if (keycode == KEY_A && wallhit(KEY_A, game) == 0)
	{
		game->chara.x -= 64;
		return (1);
	}
	if (keycode == KEY_W && wallhit(KEY_W, game) == 0)
	{
		game->chara.y -= 64;
		return (1);
	}
	if (keycode == KEY_D && wallhit(KEY_D, game) == 0)
	{
		game->chara.x += 64;
		return (1);
	}
	if (keycode == KEY_S && wallhit(KEY_S, game) == 0)
	{
		game->chara.y += 64;
		return (1);
	}
	return (0);
}

int	key_hook(int keycode, t_map *game)
{
	static int	display = 0;
	char		*string;

	if (keycode == KEY_ESC)
		destroy(game);
	if (key_dep(keycode, game) == 1)
	{
		display++;
		ft_printf("The current number of movements is: %d\n", display);
	}
	string = ft_itoa(display);
	candy(game);
	exitdoor(game);
	render_map(game);
	mlx_string_put(game->mlx, game->win, 50, 5, 0x040406, string);
	free(string);
	return (0);
}

int	init(t_map *game)
{
	int	i;

	i = 0;
	while (i < 256)
		game->sprite_mapping[i++].img = NULL;
	game->mlx = mlx_init();
	load_sprites(game);
	parse_ber_file(game);
	parse_ber_filecpy(game);
	game->win = mlx_new_window(game->mlx, game->width,
			game->height * 64, "PeepoPog");
	mlx_new_image(game->mlx, game->width, game->height * 64);
	candynum(game);
	character_pos(game);
	valid_path(game);
	render_map(game);
	mlx_hook(game->win, 17, 0, destroy, game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
