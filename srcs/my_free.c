/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 09:12:30 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/31 17:18:01 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	clear_matrix(t_metadata *meta)
{
	free(meta->p_matrix);
	meta->p_matrix = NULL;
}

void	clear_map(t_metadata *meta)
{
	if (meta->map->matrix != NULL)
		free(meta->map->matrix);
	meta->map->matrix = NULL;
	free(meta->map);
	meta->map = NULL;
}

void	clear_menu(t_metadata *meta)
{
	if (meta->menu_izo != NULL)
	{
		mlx_destroy_image(meta->mlx, meta->menu_izo);
		meta->menu_izo = NULL;
	}
	if (meta->menu_2 != NULL)
	{
		mlx_destroy_image(meta->mlx, meta->menu_2);
		meta->menu_2 = NULL;
	}
	if (meta->menu_3 != NULL)
	{
		mlx_destroy_image(meta->mlx, meta->menu_3);
		meta->menu_3 = NULL;
	}
}

void	my_free(t_metadata *meta)
{
	if (meta->img.img != NULL)
	{
		mlx_destroy_image(meta->mlx, meta->img.img);
		meta->img.img = NULL;
	}
	if (meta->p_matrix != NULL)
		clear_matrix(meta);
	if (meta->map != NULL)
		clear_map(meta);
	clear_menu(meta);
	mlx_clear_window(meta->mlx, meta->win);
	mlx_destroy_window(meta->mlx, meta->win);
	meta->end = 1;
	return ;
}
