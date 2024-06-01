/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 08:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/31 17:18:15 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	*izometric3d_2(t_map2 *map, t_point *matrix, int x_offset, int y_offset)
{
	int		i;
	int		matrix_len;

	matrix_len = map->n_cols * map->n_lines;
	i = 0;
	while (i < matrix_len)
	{
		matrix[i].x = map->matrix[i].x * map->sidelen - map->matrix[i].y
			* map->sidelen + x_offset;
		matrix[i].y = map->matrix[i].x * 0.5 * map->sidelen + map->matrix[i].y
			* 0.5 * map->sidelen - (map->matrix[i].z * (map->sidelen / sqrt(2)))
			+ y_offset;
		matrix[i].color = map->matrix[i].color;
		i++;
	}
	return (matrix);
}

t_point	*parallel_projection(t_metadata *meta, t_point *matrix,
	int x_offset, int y_offset)
{
	int		i;
	int		matrix_len;
	t_map2	*map;

	map = meta->map;
	matrix_len = map->n_cols * map->n_lines;
	i = 0;
	while (i < matrix_len)
	{
		matrix[i].x = (map->sidelen) * ((map->matrix[i].x)
				* cos(deg_to_rad(map->az)) - (map->matrix[i].y)
				* sin(deg_to_rad(map->az))) + x_offset;
		matrix[i].y = meta->camera_angle * map->sidelen * ((map->matrix[i].y)
				* cos(deg_to_rad(map->az)) + (map->matrix[i].x)
				* sin(deg_to_rad(map->az))) - (map->matrix[i].z
				* (map->sidelen / sqrt(2))) + y_offset;
		matrix[i].color = map->matrix[i].color;
		i++;
	}
	return (matrix);
}

t_point	*oblique_projection(t_map2 *map, t_point *matrix, int x_offset,
	int y_offset)
{
	int			i;
	int			matrix_len;
	float		alpha;

	matrix_len = map->n_cols * map->n_lines;
	i = 0;
	alpha = 45;
	while (i < matrix_len)
	{
		matrix[i].x = (map->sidelen * (-map->matrix[i].x + (map->matrix[i].y
						* sin(deg_to_rad(alpha))))) + x_offset;
		matrix[i].y = (map->sidelen * (-map->matrix[i].z + (map->matrix[i].y
						* cos(deg_to_rad(alpha))))) + y_offset;
		matrix[i].color = map->matrix[i].color;
		i++;
	}
	return (matrix);
}
