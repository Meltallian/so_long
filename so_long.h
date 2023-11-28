/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:17:31 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/28 17:55:00 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

# ifndef KEY_ARROWS
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_ESC 53
# endif

typedef struct s_coor {
	int	x;
	int	y;
	int	z;
	int	c;
	int	e;
	int	p;
}			t_coor;

typedef struct s_chara {
	int	x;
	int	y;
	int	a;
	int	b;
	int	found;
}			t_chara;

typedef struct s_sprite {
	void	*img;
	int		width;
	int		height;
}			t_sprite;

typedef struct s_map {
	char		**map;
	char		**mapcpy;
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			candcount;
	char		*ber;
	t_sprite	sprite_mapping[256];
	t_chara		chara;
	t_coor		coor;
}		t_map;

void	parse_ber_file(t_map *mapping);
void	parse_ber_filecpy(t_map *mapping);
int		map_height(t_map *game);
int		check_1_border(t_map *game);
int		is_rekt(t_map *game);
void	check_comps(t_map *game);
void	flood_pogging(t_map *game, int x, int y);
int		mapcpy_check(t_map *game);
int		key_dep(int keycode, t_map *game);
int		key_hook(int keycode, t_map *game);
int		init(t_map *game);
void	render_map(t_map *game);
void	load_sprites(t_map *game);
int		wallhit(int keycode, t_map *game);
int		candy(t_map *game);
void	candynum(t_map *game);
void	exitdoor(t_map *game);
void	free_map(t_map *game);
int		destroy(t_map *game);
void	character_pos(t_map *game);
void	valid_path(t_map *game);
int		invalid_cell(t_map *game);
void	anim(t_map *game);
int		anim_utils(t_map *game, char c, int i, int j);
void	anim(t_map *game);

#endif // SO_LONG_H