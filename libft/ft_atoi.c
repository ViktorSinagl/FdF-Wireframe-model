/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:40:41 by vsinagl           #+#    #+#             */
/*   Updated: 2023/10/24 19:31:23 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *instr)
{
	long		result;
	long		i;
	int			negative;

	i = 0;
	result = 0;
	negative = 0;
	while ((instr[i] >= 9 && instr[i] <= 13) || (instr[i] == 32))
		i++;
	if (instr[i] == '+' || instr[i] == '-')
	{
		if (instr[i] == '-')
			negative = 1;
		i++;
	}
	while (instr[i] >= '0' && instr[i] <= '9')
	{
		result = (result * 10) + (instr[i] - '0');
		i++;
	}
	if (negative == 1)
		return (result * -1);
	return (result);
}
