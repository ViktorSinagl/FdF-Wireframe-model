#include "../includes/fdf.h"


t_point	*izometric3D_2(t_map2 *map, t_point *matrix, int x_offset, int y_offset)
{
	int			i;
	int			matrix_len;

	matrix_len = map->n_cols * map->n_lines;
	i = 0;
	while (i < matrix_len)
	{
		matrix[i].x = map->matrix[i].x * map->sidelen - map->matrix[i].y * map->sidelen + x_offset;
		matrix[i].y = map->matrix[i].x * 0.5 * map->sidelen + map->matrix[i].y * 0.5 * map->sidelen - (map->matrix[i].z * (map->sidelen/sqrt(2))) + y_offset;
		matrix[i].color = map->matrix[i].color;
		i++;
	}
	return (matrix);
}

t_point *parallel_projection(t_metadata *meta, t_point *matrix, int x_offset, int y_offset)
{
	int		i;
	int		matrix_len;
	t_map2	*map;

	map = meta->map;
	matrix_len = map->n_cols * map->n_lines;
	i = 0;
	while(i < matrix_len)
	{
		matrix[i].x = (map->sidelen) * ((map->matrix[i].x) * cos(deg_to_rad(map->az)) - (map->matrix[i].y) * sin(deg_to_rad(map->az))) + x_offset;
		matrix[i].y = meta->camera_angle * map->sidelen * ((map->matrix[i].y) * cos(deg_to_rad(map->az)) + (map->matrix[i].x) * sin(deg_to_rad(map->az))) - (map->matrix[i].z * (map->sidelen/sqrt(2))) + y_offset;
		matrix[i].color = map->matrix[i].color;
		i++;
	}
	return (matrix);
}

t_point	*oblique_projection(t_map2 *map, t_point *matrix, int x_offset, int y_offset)
{
	int			i;
	int			matrix_len;

	matrix_len = map->n_cols * map->n_lines;
	i = 0;
	float alfa = 45;
	while (i < matrix_len)
	{
		matrix[i].x = (map->sidelen * (-map->matrix[i].x  + (map->matrix[i].y * sin(deg_to_rad(alfa))))) + x_offset;
		matrix[i].y = (map->sidelen * (-map->matrix[i].z + (map->matrix[i].y * cos(deg_to_rad(alfa))))) + y_offset;
		matrix[i].color = map->matrix[i].color;
		i++;
	}
	return (matrix);
}
