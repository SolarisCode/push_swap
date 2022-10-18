/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solariscode <solariscode@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:54:35 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/19 00:58:05 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	int		count;
	long	val;
	int		sign;

	count = 0;
	val = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == 32)
		count ++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			sign *= -1;
		count ++;
	}
	while (str[count] && str[count] >= 48 && str[count] <= 57)
	{
		val = (val * 10) + (str[count] - 48);
		count ++;
	}
	return (val * sign);
}
