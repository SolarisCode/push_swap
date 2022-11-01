/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:59:58 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:28:19 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	ft_sorted_stack(t_list *stack)
{
	t_list	*tmp;
	int		size;
	int		flag;

	size = ft_lstsize(stack);
	tmp = stack;
	flag = 0;
	while (tmp->next)
	{
		if (tmp->num < tmp->next->num)
			flag ++;
		tmp = tmp->next;
	}
	return (flag == size - 1);
}

void	ft_remain_five(t_list **stack)
{
	int	num1;
	int	num2;
	int	num3;
	int	count;

	count = -1;
	if (ft_sorted_stack(*stack))
		return ;
	else if (ft_lstsize(*stack) == 2)
		ft_sort_remain(stack, "sa");
	else
	{
		while (++count < 3)
		{
			num1 = (*stack)->num;
			num2 = (*stack)->next->num;
			num3 = (*stack)->next->next->num;
			if (num1 < num2 && num2 > num3)
				ft_reverse_rotate(stack, "rra");
			else if ((num1 > num2 && num1 > num3))
				ft_rotate_nodes(stack, "ra");
			else if (num1 > num2 && num2 < num3)
				ft_swap_nodes(stack, "sa");
		}
	}
}

void	ft_sort_five(t_list **stack_a, t_list **stack_b)
{
	int	pivot;
	int	top;
	int	bottom;
	int	count;
	int	size;

	if (ft_lstsize(*stack_a) == 2)
	{
		ft_sort_remain(stack_a, "sa");
		return ;
	}
	size = ft_lstsize(*stack_a) / 2;
	count = -1;
	pivot = ft_get_pivot(*stack_a);
	while (++count < size)
	{
		top = ft_top_best(*stack_a, pivot, 1);
		bottom = ft_bottom_best(*stack_a, pivot, 1);
		if (top >= 0 && bottom >= 0)
			ft_push_b(stack_a, stack_b, top, bottom);
	}
	ft_remain_five(stack_a);
}

void	ft_small_stack(char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		count;

	if (!ft_check_nbr(argv) || ft_sorted_max(argv))
		return ;
	stack_a = ft_stack_a(argv);
	if (!stack_a)
		return ;
	ft_get_index(stack_a);
	stack_b = NULL;
	ft_sort_five(&stack_a, &stack_b);
	if (ft_lstsize(stack_b) > 1 && stack_b->index \
			!= ft_lstlast(stack_a)->index + 1)
		ft_sort_remain(&stack_b, "sb");
	count = -1;
	while (stack_b && ++count <= ft_lstsize(stack_b))
	{
		ft_push_node(&stack_b, &stack_a, "pa");
		ft_rotate_nodes(&stack_a, "ra");
	}
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
}
