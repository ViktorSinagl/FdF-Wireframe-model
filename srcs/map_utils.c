/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:12:30 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/31 17:18:01 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_matrix_width(char *line)
{
	int	count;

	count = 0;
	while (1)
	{
		while (*line == ' ' || *line == '-' || *line == '+')
			line++;
		if (ft_isdigit(*line))
			count++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ',')
		{
			line++;
			while (ft_isalpha(*line) || ft_isdigit(*line))
				line++;
			while (*line == ' ')
				line++;
		}
		if (*line == '\n' || *line == '\0')
			break ;
	}
	return (count);
}

int	get_color(char *line)
{
	char	str_dup[11];
	int		i;
	int		number;

	i = 0;
	while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
	{
		if (i > 8)
			break ;
		str_dup[i] = ft_toupper(line[i]);
		i++;
	}
	str_dup[i] = '\0';
	number = (ft_atoi_base("0123456789ABCDEF", &str_dup[2]));
	return (number);
}
