/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:44:32 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:13:00 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	ft_check_nbr(char **argv)
{
	int	count;
	int	index;

	count = -1;
	while (argv[++count])
	{
		index = -1;
		if (argv[count][0] == '-')
			index ++;
		while (argv[count][++index])
			if (!ft_isdigit(argv[count][index]))
				return (ft_putstr_fd("Error\n", 2), false);
		index = -1;
		while (argv[++index])
			if (count != index && !ft_strcmp(argv[count], argv[index]))
				return (ft_putstr_fd("Error\n", 2), false);
	}
	return (true);
}

bool	ft_check_max(char **argv)
{
	int	count;

	count = -1;
	while (argv[++count])
		if (ft_atolong(argv[count]) > INT_MAX || \
				ft_atolong(argv[count]) < INT_MIN)
			return (true);
	return (false);
}

bool	ft_sorted_max(char **argv)
{
	int	count;

	if (ft_check_max(argv))
		return (true);
	count = -1;
	while (argv[++count + 1])
		if (ft_atolong(argv[count]) > ft_atolong(argv[count + 1]))
			return (false);
	return (true);
}
