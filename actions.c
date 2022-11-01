/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:56:45 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:20:34 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_b(t_list **stack_a, t_list **stack_b, int top, int bottom)
{
	if (top < 0 || bottom < 0)
		return ;
	else if (top == 0)
		ft_push_node(stack_a, stack_b, "pb");
	else if (top == 1)
	{
		ft_swap_nodes(stack_a, "sa");
		ft_push_node(stack_a, stack_b, "pb");
	}
	else if (top <= bottom)
	{
		ft_rotate_nodes(stack_a, "ra");
		ft_push_b(stack_a, stack_b, top - 1, bottom + 1);
	}
	else
	{
		ft_reverse_rotate(stack_a, "rra");
		if (bottom - 1 < 0)
			ft_push_node(stack_a, stack_b, "pb");
		ft_push_b(stack_a, stack_b, top + 1, bottom - 1);
	}
}

void	ft_push_a(t_list **stack_b, t_list **stack_a, int top, int bottom)
{
	if (top < 0 || bottom < 0)
		return ;
	else if (top == 0)
		ft_push_node(stack_b, stack_a, "pa");
	else if (top == 1)
	{
		ft_swap_nodes(stack_b, "sb");
		ft_push_node(stack_b, stack_a, "pa");
	}
	else if (top <= bottom)
	{
		ft_rotate_nodes(stack_b, "rb");
		ft_push_a(stack_b, stack_a, top - 1, bottom + 1);
	}
	else
	{
		ft_reverse_rotate(stack_b, "rrb");
		if (bottom - 1 < 0)
			ft_push_node(stack_b, stack_a, "pa");
		ft_push_a(stack_b, stack_a, top + 1, bottom - 1);
	}
}

int	ft_bottom_best(t_list *stack, int pivot, int flag)
{
	t_list	*tmp;
	int		bottom;

	tmp = ft_lstlast(stack);
	bottom = -1;
	while (tmp)
	{
		bottom ++;
		if (flag)
		{
			if (tmp->num > pivot)
				return (bottom);
		}
		else
			if (tmp->num < pivot)
				return (bottom);
		tmp = tmp->prev;
	}
	return (-1);
}

int	ft_top_best(t_list *stack, int pivot, int flag)
{
	t_list	*tmp;
	int		top;

	tmp = stack;
	top = -1;
	while (tmp)
	{
		top ++;
		if (flag)
		{
			if (tmp->num > pivot)
				return (top);
		}
		else
			if (tmp->num < pivot)
				return (top);
		tmp = tmp->next;
	}
	return (-1);
}

void	ft_send_pivot(t_list **stack_a, t_list **stack_b, int pivot)
{
	t_list	*tmp;
	int		count;
	int		found;

	tmp = *stack_a;
	count = -1;
	found = -1;
	while (tmp)
	{
		count ++;
		if (tmp->num == pivot)
			found = count;
		tmp = tmp->next;
	}
	if (found < 3 && found >= 0)
		ft_push_b(stack_a, stack_b, found, 4);
	else if (found == 3)
		ft_push_b(stack_a, stack_b, found, 0);
}
