/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:45 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/20 17:28:47 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			mlx_put_image_to_window(game->mlx, game->win,
				 game->sprite_mapping[tile].img, j * 64, i * 64);
			j++;
		}
		j = 0;
		i++;
	}
}

int main()
{
	t_map	game;
	int		fd;
	int		i;

	game.map = 0;
	game.mlx = mlx_init();
	load_sprites(&game);
	i = 0;
	fd = open("map.ber", O_RDONLY);
	parse_ber_file(fd, &game);
	close(fd);
	game.win = mlx_new_window(game.mlx, ft_strlen(game.map[0])*64 - 64, game.height*64 - 64, "PeepoPog");
	render_map(&game);
//	mlx_loop(game.mlx);
	while (game.map[i])
	{
		free(game.map[i]);
		i++;
	}
	free(game.map);
	return 0;
}
