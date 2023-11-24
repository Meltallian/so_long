/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:17:31 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/24 15:32:25 by jbidaux          ###   ########.fr       */
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

typedef	struct s_map {
	char	**map;
	char	**mapcpy;
	void	*mlx;
	void	*win;
	int	width;
	int	height;
	int	candcount;
	t_sprite sprite_mapping[256];
	t_chara chara;
}		t_map;

void	parse_ber_file(t_map *mapping);
void	parse_ber_filecpy(t_map *mapping);
int		map_height(void);

#endif // SO_LONG_H