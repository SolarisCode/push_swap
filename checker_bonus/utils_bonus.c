/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:59:39 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 18:15:37 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

long	ft_atolong(const char *str)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;

	count = 0;
	while (s1[count] && s2[count] && s1[count] == s2[count])
		count ++;
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}

bool	ft_check_op(char *op)
{
	if (!ft_strnstr("sasbssrarbrrrrarrbrrrpbpa", op, 25))
	{
		ft_putstr_fd("Error\n", 2);
		return (false);
	}
	return (true);
}

void	ft_free_op(char **list_op)
{
	int	count;

	count = -1;
	while (list_op[++count])
		free(list_op[count]);
	free(list_op);
}
