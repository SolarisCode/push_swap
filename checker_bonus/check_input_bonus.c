/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:01:42 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 18:18:27 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

bool	ft_check_max(char **argv)
{
	int	count;

	count = -1;
	while (argv[++count])
		if (ft_atolong(argv[count]) > INT_MAX || \
				ft_atolong(argv[count]) < INT_MIN)
			return (ft_putstr_fd("Error\n", 2), true);
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
	return (ft_putstr_fd("OK\n", 1), true);
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
				return (ft_putstr_fd("Error\n", 2), false);
		index = -1;
		while (argv[++index])
			if (count != index && !ft_strcmp(argv[count], argv[index]))
				return (ft_putstr_fd("Error\n", 2), false);
	}
	return (true);
}

char	**ft_operation(void)
{
	char	*tmp;
	char	*str_op;
	char	**list_op;
	int		count;

	str_op = NULL;
	tmp = get_next_line(0);
	while (tmp)
	{
		str_op = ft_strjoin_free(str_op, tmp);
		free(tmp);
		tmp = get_next_line(0);
	}
	list_op = ft_split(str_op, '\n');
	free(str_op);
	count = -1;
	while (list_op[++count])
		if (!ft_check_op(list_op[count]))
			return (ft_free_op(list_op), NULL);
	return (list_op);
}
