/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:49:04 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:29:19 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_stack(t_list **stack)
{
	t_list	*tmp;

	tmp = *stack;
	while (tmp)
	{
		*stack = (*stack)->next;
		free(tmp);
		tmp = *stack;
	}
}

t_list	*ft_stack_a(char **argv)
{
	t_list	*stack_a;
	int		count;

	count = 0;
	stack_a = ft_lstnew((int)ft_atolong(argv[0]));
	if (!stack_a)
		return (NULL);
	while (argv[++count])
		ft_lstadd_back(&stack_a, ft_lstnew((int)ft_atolong(argv[count])));
	ft_get_index(stack_a);
	return (stack_a);
}

t_list	*ft_stack_b(t_list **stack_a, t_list **stack_b)
{
	static int	group;
	int			pivot;

	if (ft_lstsize(*stack_a) < 3)
		return (*stack_b);
	pivot = ft_get_pivot(*stack_a);
	if (!ft_check_smaller(*stack_a, pivot) && !(ft_lstsize(*stack_a) < 3))
	{
		ft_send_pivot(stack_a, stack_b, pivot);
		return (*stack_b);
	}
	ft_create_groups(stack_a, stack_b, pivot);
	ft_set_groups(stack_b, ++group);
	ft_stack_b(stack_a, stack_b);
	return (*stack_b);
}

void	ft_check_execute(char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	if (!ft_check_nbr(argv) || ft_sorted_max(argv))
		return ;
	stack_a = ft_stack_a(argv);
	if (!stack_a)
		return ;
	stack_b = NULL;
	stack_b = ft_stack_b(&stack_a, &stack_b);
	ft_sort_remain(&stack_a, "sa");
	ft_sort_stack(&stack_a, &stack_b);
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	else if (argc == 2)
	{
		ft_check_nbr(&argv[1]);
		ft_check_max(&argv[1]);
		return (1);
	}
	else if (argc < 7)
		ft_small_stack(&argv[1]);
	else
		ft_check_execute(&argv[1]);
	return (0);
}
