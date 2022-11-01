/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:47:03 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:13:35 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_reverse_rotate(t_list **stack, char *action)
{
	t_list	*head;

	head = *stack;
	head = ft_lstlast(*stack);
	head->next = *stack;
	(*stack)->prev = head;
	*stack = head;
	head->prev->next = NULL;
	head->prev = NULL;
	ft_printf("%s\n", action);
}

void	ft_rotate_nodes(t_list **stack, char *action)
{
	t_list	*tail;

	tail = ft_lstlast(*stack);
	tail->next = *stack;
	(*stack)->prev = tail;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	tail->next->next = NULL;
	ft_printf("%s\n", action);
}

void	ft_push_node(t_list **src, t_list **dst, char *action)
{
	t_list	*tmp;

	if (!*dst)
	{
		*dst = ft_lstnew((*src)->num);
		if (!*dst)
			return ;
		(*dst)->index = (*src)->index;
		tmp = *src;
		*src = (*src)->next;
		(*src)->prev = NULL;
		ft_printf("pb\n");
		free(tmp);
		return ;
	}
	(*dst)->prev = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	(*dst)->prev->next = *dst;
	*dst = (*dst)->prev;
	(*dst)->prev = NULL;
	ft_printf("%s\n", action);
}

void	ft_swap_nodes(t_list **stack, char *action)
{
	t_list	*head;

	head = (*stack)->next;
	(*stack)->next = (*stack)->next->next;
	if ((*stack)->next)
		(*stack)->next->prev = (*stack);
	(*stack)->prev = head;
	head->next = *stack;
	head->prev = NULL;
	*stack = head;
	ft_printf("%s\n", action);
}
