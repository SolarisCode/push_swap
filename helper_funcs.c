/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:49:59 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:16:48 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_get_pivot(t_list *stack)
{
	t_list	*tmp;
	int		*array;
	int		size;
	int		count;

	size = ft_lstsize(stack);
	array = (int *)ft_calloc(size, sizeof(int));
	if (!array)
		return (0);
	tmp = stack;
	count = 0;
	while (tmp)
	{
		array[count] = tmp->num;
		tmp = tmp->next;
		count ++;
	}
	ft_quicksort(array, 0, count - 1);
	while (count > 75)
		count /= 2;
	count = array[count / 2];
	free(array);
	return (count);
}

void	ft_set_groups(t_list **stack_b, int group)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = *stack_b;
	while (tmp)
	{
		if (tmp->group == 0)
			tmp->group = group;
		tmp = tmp->next;
	}
}

bool	ft_check_smaller(t_list *stack, int pivot)
{
	t_list	*tmp;
	bool	found;

	found = false;
	tmp = stack;
	while (tmp)
	{
		if (tmp->num < pivot)
			found = true;
		tmp = tmp->next;
	}
	return (found);
}
