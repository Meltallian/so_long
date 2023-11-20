/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:17:31 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/20 17:09:34 by jbidaux          ###   ########.fr       */
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
/*
typedef struct	s_data {
	void	*img[5];
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data; */

typedef struct s_sprite {
	void	*img;
	int		width;
	int		height;
}			t_sprite;

typedef	struct s_map {
	char	**map;
	void	*mlx;
	void	*win;
	int	width;
	int	height;
	int	i;
	t_sprite sprite_mapping[256];
}		t_map;

void	parse_ber_file(int fd, t_map *mapping);
void	ft_free(char **map, int i);
int		map_height(void);

#endif // SO_LONG_H