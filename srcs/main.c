/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/31 14:08:31 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <unistd.h>

int	window_init(t_metadata *meta)
{
	meta->mlx = mlx_init();
	if (meta->mlx == NULL)
	{
		my_free(meta);
		(put_err_fd(MLX_MLX, 2), exit(2));
	}
	meta->win = mlx_new_window(meta->mlx, WIDTH, HEIGHT, "Good grade plz :)");
	if (meta->win == NULL)
	{
		my_free(meta);
		(put_err_fd(MLX_WIN, 2), exit(2));
	}
	meta->img.img = create_img(meta->mlx);
	if (meta->img.img == NULL)
	{
		my_free(meta);
		(put_err_fd(MLX_IMG, 2), exit(2));
	}
	meta->img.addr = mlx_get_data_addr(meta->img.img,
			&meta->img.bits_per_pixel,
			&meta->img.line_length,
			&meta->img.endian);
	return (0);
}

int	process_args(int argc, char **argv, t_metadata *meta)
{
	int	fd;

	if (argc != 2)
		(put_err_fd(ERR_ARG, 2), exit(1));
	if (check_ending(argv[1]) == 0)
		(put_err_fd(ERR_FILE, 2), exit(1));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		(put_err_fd(ERR_READ, 2), exit(1));
	meta->map = create_map(fd, meta, argv);
	close(fd);
	if (meta->map == NULL)
	{
		free(meta);
		(put_err_fd(ERR_MAP, 2), exit(1));
	}
	meta->matrix_len = meta->map->n_cols * meta->map->n_lines;
	meta->p_matrix = (t_point *)malloc(sizeof(t_point) * meta->matrix_len);
	return (0);
}

int	drawing(void *param)
{
	t_metadata	*meta;

	meta = param;
	if (meta == NULL || meta->mlx == NULL)
		return (1);
	if (meta->end == 1)
		return (0);
	black_me_pls(meta);
	draw_mesh(meta);
	if (meta->projection == 1)
		mlx_put_image_to_window(meta->mlx, meta->win, meta->menu_izo, 50, 50);
	else if (meta->projection == 2)
		mlx_put_image_to_window(meta->mlx, meta->win, meta->menu_2, 50, 50);
	else if (meta->projection == 3)
		mlx_put_image_to_window(meta->mlx, meta->win, meta->menu_3, 50, 50);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img.img,
		MENUWIDTH + 60, 0);
	return (0);
}

//meta->projection 1: izometric
//meta->projection 2: parallel
//meta->projection 3: oblique
int	run_program(t_metadata *meta)
{
	izometric3d_2(meta->map, meta->p_matrix, meta->map->x_offset,
		meta->map->y_offset);
	mlx_loop_hook(meta->mlx, &drawing, meta);
	mlx_hook(meta->win, 33, 1L << 17, &close_program, meta);
	mlx_key_hook(meta->win, &key_control, meta);
	mlx_loop(meta->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_metadata	meta;

	process_args(argc, argv, &meta);
	meta.projection = 1;
	meta.camera_angle = 0.45;
	meta.end = 0;
	window_init(&meta);
	create_menu(&meta);
	run_program(&meta);
	mlx_destroy_display(meta.mlx);
	free(meta.mlx);
	return (0);
}
