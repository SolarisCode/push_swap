/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:53:45 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:18:23 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_find_index(int *array, int num, int end)
{
	int		mid;
	int		low;

	low = 0;
	mid = 0;
	while (end >= 1)
	{
		mid = (end + low) / 2;
		if (num == array[mid])
			return (mid);
		else if (num < array[mid])
			end = mid;
		else
			low = mid + 1;
	}
	return (mid);
}

void	ft_set_index(t_list *stack, int *array)
{
	t_list	*tmp;
	int		size;

	size = ft_lstsize(stack);
	tmp = stack;
	while (tmp)
	{
		tmp->index = ft_find_index(array, tmp->num, size - 1);
		tmp = tmp->next;
	}
}

void	ft_get_index(t_list *stack)
{
	t_list	*tmp;
	int		*array;
	int		size;
	int		count;

	size = ft_lstsize(stack);
	array = (int *)ft_calloc(size, sizeof(int));
	if (!array)
		return ;
	tmp = stack;
	count = 0;
	while (tmp)
	{
		array[count] = tmp->num;
		tmp = tmp->next;
		count ++;
	}
	ft_quicksort(array, 0, size - 1);
	ft_set_index(stack, array);
	free(array);
}

int	ft_bottom_index(t_list *stack, int index)
{
	t_list	*tmp;
	int		bottom;

	tmp = ft_lstlast(stack);
	bottom = -1;
	while (tmp)
	{
		bottom ++;
		if (tmp->index == index)
			return (bottom);
		tmp = tmp->prev;
	}
	return (-1);
}

int	ft_top_index(t_list *stack, int index)
{
	t_list	*tmp;
	int		top;

	tmp = stack;
	top = -1;
	while (tmp)
	{
		top ++;
		if (tmp->index == index)
			return (top);
		tmp = tmp->next;
	}
	return (-1);
}
