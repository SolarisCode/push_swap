/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:06:16 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 18:22:52 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	ft_double_action(t_list **stack_a, t_list **stack_b, char *action)
{
	if (!ft_strcmp(action, "ss"))
	{
		ft_swap_nodes(stack_a);
		ft_swap_nodes(stack_b);
	}
	if (!ft_strcmp(action, "rr"))
	{
		ft_rotate_nodes(stack_a);
		ft_rotate_nodes(stack_b);
	}
	if (!ft_strcmp(action, "rrr"))
	{
		ft_reverse_rotate(stack_a);
		ft_reverse_rotate(stack_b);
	}
}

void	ft_actions(t_list **stack_a, t_list **stack_b, char **list_op)
{
	int	count;

	count = -1;
	while (list_op[++count])
	{
		if (!ft_strcmp(list_op[count], "sa"))
			ft_swap_nodes(stack_a);
		else if (!ft_strcmp(list_op[count], "sb"))
			ft_swap_nodes(stack_b);
		else if (!ft_strcmp(list_op[count], "ra"))
			ft_rotate_nodes(stack_a);
		else if (!ft_strcmp(list_op[count], "rb"))
			ft_rotate_nodes(stack_b);
		else if (!ft_strcmp(list_op[count], "rra"))
			ft_reverse_rotate(stack_a);
		else if (!ft_strcmp(list_op[count], "rrb"))
			ft_reverse_rotate(stack_b);
		else if (ft_strnstr("rrssrrr", list_op[count], 7))
			ft_double_action(stack_a, stack_b, list_op[count]);
		else if (!ft_strcmp(list_op[count], "pa"))
			ft_push_node(stack_b, stack_a);
		else if (!ft_strcmp(list_op[count], "pb"))
			ft_push_node(stack_a, stack_b);
	}
}
