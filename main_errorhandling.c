/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:49:04 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/16 00:00:10 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf/ft_printf_bonus.h"
#include "ft_printf/libft/libft.h"
#include <stdbool.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;

	count = 0;
	while (s1[count] && s2[count] && s1[count] == s2[count])
		count ++;
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}

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
				return (ft_putstr_fd("Error\n", 1), false);
		index = -1;
		while (argv[++index])
			if (count != index && !ft_strcmp(argv[count], argv[index]))
					return (ft_putstr_fd("Error\n", 1), false);
	}
	return (true);
}

bool	ft_check_max(char **argv, int *array)
{
	int		count;
	bool	max;

	count = -1;
	max = false;
	while (argv[++count])
	{
		if (argv[count][0] == '-' && array[count] > 0)
			max = true;
		else if (argv[count][0] != '-' && array[count] < 0)
			max = true;
	}
	free(array);
	if (max)
		ft_putstr_fd("Error\n", 1);
	return (max);
}

bool	ft_sorted_max(char **argv)
{
	int	size;
	int	count;
	int	*array;

	size = -1;
	while (argv[++size]);
	array = (int *)ft_calloc(size, sizeof(int));
	if (!array)
		return (NULL);
	count = -1;
	while (argv[++count])
		array[count] = ft_atoi(argv[count]);
	count = 0;
	while(count <= size - 2 && array[count] < array[count + 1])
		count ++;
	if (count == size - 1)
		return (free(array), true);
	return (ft_check_max(argv, array));
}

void	ft_check_input(char **argv)
{
	if (!ft_check_nbr(argv) || ft_sorted_max(argv))
		return ;
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	else
		ft_check_input(&argv[1]);
	return (0);
}
