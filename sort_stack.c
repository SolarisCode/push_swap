/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:03:31 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:24:54 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_create_groups(t_list **stack_a, t_list **stack_b, int pivot)
{
	int		top;
	int		bottom;

	top = ft_top_best(*stack_a, pivot, 0);
	bottom = ft_bottom_best(*stack_a, pivot, 0);
	if ((top < 0 && bottom < 0) || !ft_check_smaller(*stack_a, pivot))
		return ;
	ft_push_b(stack_a, stack_b, top, bottom);
	ft_create_groups(stack_a, stack_b, pivot);
}

void	ft_sort_stack(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;
	int		top;
	int		bottom;

	tmp = *stack_a;
	if (tmp->index == 0)
		return ;
	top = ft_top_index(*stack_b, tmp->index - 1);
	bottom = ft_bottom_index(*stack_b, tmp->index - 1);
	ft_push_a(stack_b, stack_a, top, bottom);
	ft_sort_stack(stack_a, stack_b);
}

void	ft_sort_remain(t_list **stack, char *action)
{
	t_list	*head;

	head = *stack;
	if (head->num > (*stack)->next->num)
	{
		ft_printf("%s\n", action);
		head = (*stack)->next;
		head->prev = NULL;
		head->next = *stack;
		(*stack)->prev = head;
		(*stack)->next = NULL;
		*stack = head;
	}
}
