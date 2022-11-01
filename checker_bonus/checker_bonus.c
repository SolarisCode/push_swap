/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:20:47 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 18:14:32 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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
	return (stack_a);
}

bool	ft_sorted_stack(t_list *stack)
{
	t_list	*tmp;

	tmp = stack;
	while (tmp->next)
	{
		if (tmp->num > tmp->next->num)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

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

void	ft_check_execute(char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	char	**list_op;

	if (!ft_check_nbr(argv) || ft_sorted_max(argv))
		return ;
	stack_a = ft_stack_a(argv);
	if (!stack_a)
		return ;
	stack_b = NULL;
	list_op = ft_operation();
	if (!list_op)
	{
		ft_free_stack(&stack_a);
		return ;
	}
	ft_actions(&stack_a, &stack_b, list_op);
	if (ft_sorted_stack(stack_a) && !stack_b)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	ft_free_op(list_op);
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
	else
		ft_check_execute(&argv[1]);
	return (0);
}
