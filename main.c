/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:55:38 by jbidaux           #+#    #+#             */
/*   Updated: 2023/11/17 13:03:40 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct	s_data {
	void	*img[5];
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	char	*relative_path[5];
	int		img_width;
	int		img_height;
	t_data	img;
	relative_path[0] = "images/ground.xpm";
	relative_path[1] = "images/tree.xpm";
	relative_path[2] = "images/kawai.xpm";
	relative_path[3] = "images/candy_l.xpm";
	relative_path[4] = "images/gate.xpm";

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 128, 128, "Pog"); // 100 100 = size of the window
	img.img[0] = mlx_xpm_file_to_image(mlx, relative_path[0], &img_width, &img_height);
	img.addr = mlx_get_data_addr(img.img[0], &img.bits_per_pixel, &img.line_length,
								&img.endian);

	img.img[1] = mlx_xpm_file_to_image(mlx, relative_path[1], &img_width, &img_height);
//	img.addr = mlx_get_data_addr(img.img[1], &img.bits_per_pixel, &img.line_length,
//								&img.endian);

	img.img[2] = mlx_xpm_file_to_image(mlx, relative_path[2], &img_width, &img_height);
//	img.addr = mlx_get_data_addr(img.img[2], &img.bits_per_pixel, &img.line_length,
//								&img.endian);

	img.img[3] = mlx_xpm_file_to_image(mlx, relative_path[3], &img_width, &img_height);
//	img.addr = mlx_get_data_addr(img.img[3], &img.bits_per_pixel, &img.line_length,
//								&img.endian);

	img.img[4] = mlx_xpm_file_to_image(mlx, relative_path[4], &img_width, &img_height);
//	img.addr = mlx_get_data_addr(img.img[4], &img.bits_per_pixel, &img.line_length,
//								&img.endian);
//	mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
//	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img[0], 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, img.img[1], 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, img.img[0], 64, 0);
	mlx_put_image_to_window(mlx, mlx_win, img.img[2], 64, 0);
	mlx_put_image_to_window(mlx, mlx_win, img.img[0], 0, 64);
	mlx_put_image_to_window(mlx, mlx_win, img.img[3], 0, 64);
	mlx_put_image_to_window(mlx, mlx_win, img.img[0], 64, 64);
	mlx_put_image_to_window(mlx, mlx_win, img.img[4], 64, 64);
	mlx_loop(mlx);
}
