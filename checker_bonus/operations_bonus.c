/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:04:09 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 18:21:18 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	ft_reverse_rotate(t_list **stack)
{
	t_list	*head;

	if (!*stack)
		return ;
	head = *stack;
	head = ft_lstlast(*stack);
	head->next = *stack;
	(*stack)->prev = head;
	*stack = head;
	head->prev->next = NULL;
	head->prev = NULL;
}

void	ft_rotate_nodes(t_list **stack)
{
	t_list	*tail;

	if (!*stack)
		return ;
	tail = ft_lstlast(*stack);
	tail->next = *stack;
	(*stack)->prev = tail;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	tail->next->next = NULL;
}

void	ft_push_node(t_list **src, t_list **dst)
{
	t_list	*tmp;

	if (!*src)
		return ;
	if (!*dst)
	{
		*dst = ft_lstnew((*src)->num);
		if (!*dst)
			return ;
		(*dst)->index = (*src)->index;
		tmp = *src;
		*src = (*src)->next;
		(*src)->prev = NULL;
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
}

void	ft_swap_nodes(t_list **stack)
{
	t_list	*head;

	if (!(*stack))
		return ;
	head = (*stack)->next;
	(*stack)->next = (*stack)->next->next;
	if ((*stack)->next)
		(*stack)->next->prev = (*stack);
	(*stack)->prev = head;
	head->next = *stack;
	head->prev = NULL;
	*stack = head;
}
