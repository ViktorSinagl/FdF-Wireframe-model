/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 08:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/31 17:18:15 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	fill_matrix(t_map2 *map, char *line, int y, int len)
{
	int	x;

	x = 0;
	while (x < len)
	{
		map->matrix[y * map->n_cols + x].x = (float)(-map->n_cols / 2 + x);
		map->matrix[y * map->n_cols + x].y = (float)(-map->n_lines / 2 + y);
		while (*line == ' ')
			line++;
		map->matrix[y * map->n_cols + x].z = (float)ft_atoi(line);
		while (ft_isdigit(*line) || *line == '+' || *line == '-')
			line++;
		if (*line == ',')
		{
			line++;
			map->matrix[y * map->n_cols + x].color = get_color(line);
			while (ft_isalpha(*line) || ft_isdigit(*line))
				line++;
		}
		else
			map->matrix[y * map->n_cols + x].color = DEFAULTCOLOR;
		if (*line == '\n' || '\0')
			break ;
		x++;
	}
}

void	map_default_values(t_map2 *map)
{
	int	sidelen;

	if (((WIDTH - MENUWIDTH) / map->n_cols) > (HEIGHT / map->n_lines))
		sidelen = ((WIDTH - MENUWIDTH) / map->n_cols);
	else
		sidelen = (HEIGHT / map->n_lines);
	if (sidelen > 5)
		map->sidelen = sidelen / 3;
	else
		map->sidelen = 5;
	map->x_offset = ((WIDTH - MENUWIDTH) / 2);
	map->y_offset = (HEIGHT / 2);
	map->az = 0;
}

void	*map_init(char **argv)
{
	char	*line;
	int		fd;
	t_map2	*map;
	char	*tmp;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	map = (t_map2 *)malloc(sizeof(t_map2));
	if (line == NULL || *line == '\0' || map == NULL
		|| get_matrix_width(line) < 0)
		return (NULL);
	map->n_cols = get_matrix_width(line);
	map->n_lines = 0;
	while (line != NULL)
	{
		tmp = line;
		if (map->n_lines > 0 && map->n_cols != get_matrix_width(line))
			return (NULL);
		line = get_next_line(fd);
		free(tmp);
		map->n_lines++;
	}
	map->matrix = (t_element *)malloc(sizeof(t_element)
			* map->n_lines * map->n_cols);
	return (map);
}

t_map2	*create_map(int fd, t_metadata *meta, char **argv)
{
	t_map2	*map;
	char	*line;
	char	*tmp;
	int		i;

	map = map_init(argv);
	if (map == NULL)
	{
		my_free(meta);
		(put_err_fd(ERR_MAP, 2), exit(1));
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = line;
		fill_matrix(map, line, i, map->n_cols);
		line = get_next_line(fd);
		free(tmp);
		i++;
	}
	map_default_values(map);
	return (map);
}
