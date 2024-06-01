/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:10:10 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/01 14:18:15 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	close_program(t_metadata *vars)
{
	my_free(vars);
	return (0);
}

void	zoom(int keycode, t_metadata *meta)
{
	int	zoom;

	if (meta->map->sidelen < 10)
		zoom = 1;
	else if (meta->map->sidelen < 30)
		zoom = 3;
	else
		zoom = 5;
	if (keycode == 'x' && meta->map->sidelen < 100)
		meta->map->sidelen += zoom;
	else if (keycode == 'z' && meta->map->sidelen > 2)
		meta->map->sidelen -= zoom;
	if (meta->projection == 1)
		izometric3d_2(meta->map, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
	else if (meta->projection == 2)
		parallel_projection(meta, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
	else if (meta->projection == 3)
		oblique_projection(meta->map, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
}

void	change_projection(t_metadata *meta)
{
	int	rot_diff;

	rot_diff = -meta->map->az;
	if (meta->projection == 1)
	{
		meta->projection = 2;
		rotate_map(meta->map, 0, 0, rot_diff + 22.5);
		parallel_projection(meta, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
	}
	else if (meta->projection == 2)
	{
		meta->projection = 3;
		rotate_map(meta->map, 0, 0, rot_diff);
		oblique_projection(meta->map, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
	}
	else if (meta->projection == 3)
	{
		meta->projection = 1;
		izometric3d_2(meta->map, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
	}
}

void	rotate_projection(int keycode, t_metadata *meta)
{
	int	rot;

	rot = DEF_ROT;
	if (meta->projection == 2)
		rot = 5;
	if (ft_tolower(keycode) == 'q')
		rotate_map(meta->map, 0, 0, rot);
	else if (ft_tolower(keycode) == 'e')
		rotate_map(meta->map, 0, 0, -rot);
	else if (ft_tolower(keycode) == 'r' && meta->camera_angle < 1)
		meta->camera_angle += 0.05;
	else if (ft_tolower(keycode) == 'f' && meta->camera_angle > 0)
		meta->camera_angle -= 0.05;
	if (meta->projection == 1)
		izometric3d_2(meta->map, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
	else if (meta->projection == 2)
		parallel_projection(meta, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
	else if (meta->projection == 3)
		oblique_projection(meta->map, meta->p_matrix,
			meta->map->x_offset, meta->map->y_offset);
}

int	key_control(int keycode, void *param)
{
	t_metadata	*meta;
	int			move;

	meta = param;
	move = DEF_MOVE;
	if (keycode == ESC)
		close_program(meta);
	else if (keycode == UP || ft_tolower(keycode) == 'w')
		offset_matrix(meta, 0, -move);
	else if (keycode == DOWN || ft_tolower(keycode) == 's')
		offset_matrix(meta, 0, move);
	else if (keycode == LEFT || ft_tolower(keycode) == 'a')
		offset_matrix(meta, -move, 0);
	else if (keycode == RIGHT || ft_tolower(keycode) == 'd')
		offset_matrix(meta, move, 0);
	else if (ft_tolower(keycode) == 'q' || ft_tolower(keycode) == 'e'
		|| ft_tolower(keycode) == 'r' || ft_tolower(keycode) == 'f')
		rotate_projection(keycode, meta);
	else if (ft_tolower(keycode) == 'c')
		change_projection(meta);
	else
		zoom(keycode, meta);
	return (0);
}
