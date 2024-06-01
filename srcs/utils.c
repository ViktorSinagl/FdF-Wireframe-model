/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:10:10 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/01 14:18:15 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	check_ending(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == 'f' && str[i - 2] == 'd' && str[i - 3] == 'f')
		return (1);
	return (0);
}

int	put_err_fd(char *s, int fd)
{
	int	i;

	if (s == NULL || fd < 0)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	put_color(t_color color)
{
	return (((color.ovalue & 0xFF) << 24) | ((color.r & 0xFF) << 16)
		| ((color.g & 0xFF) << 8) | (color.b & 0xFF));
}

int	put_color_test(int r, int g, int b, int ovalue)
{
	return (ovalue << 24 | r << 16 | g << 8 | b);
}
