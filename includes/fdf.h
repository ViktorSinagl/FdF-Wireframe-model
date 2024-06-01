/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 08:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/31 17:18:15 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../get_next_line/get_next_line_bonus.h"
# include "../.mlx_linux/mlx.h"
# include "../libft/libft.h"
# include "defines.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/keysym.h>

//mlx_functions
void	*create_img(void *mlx);
t_map2	*create_map(int fd, t_metadata *meta, char **argv);
int		close_program(t_metadata *vars);
//graphic functions
void	my_mlx_pixel_put(t_imgdata *data, int x, int y, int color);
void	putline_dda(t_imgdata *data, t_point a, t_point b);
void	putline_bresemhans(t_imgdata *data, t_point a, t_point b, int color);
void	create_menu(t_metadata *meta);
void	draw_mesh(t_metadata *meta);
//projection functions
t_point	*izometric3d_2(t_map2 *map, t_point *matrix,
			int x_offset, int y_offset);
t_point	*parallel_projection(t_metadata *meta,
			t_point *matrix, int x_offset, int y_offset);
t_point	*oblique_projection(t_map2 *map, t_point *matrix,
			int x_offset, int y_offset);
float	deg_to_rad(float deg);
void	rotate_map(t_map2 *map, int ax, int ay, int az);
void	offset_matrix(t_metadata *meta, int x_offset, int y_offset);
void	black_me_pls(t_metadata *meta);
// utils functions
int		get_matrix_width(char *line);
int		put_err_fd(char *s, int fd);
void	my_free(t_metadata *meta);
int		put_color(t_color color);
int		get_color(char *line);
int		key_control(int keycode, void *param);
int		check_ending(char *str);

#endif
