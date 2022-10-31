/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:20:47 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/31 23:01:19 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "ft_printf/ft_printf_bonus.h"
#include "ft_printf/libft/libft.h"

long	ft_atolong(const char *str)
{
	int		count;
	long	val;
	int		sign;

	count = 0;
	val = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == 32)
		count ++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			sign *= -1;
		count ++;
	}
	while (str[count] && str[count] >= 48 && str[count] <= 57)
	{
		val = (val * 10) + (str[count] - 48);
		count ++;
	}
	return (val * sign);
}

bool	ft_check_max(char **argv)
{
	int	count;

	count = -1;
	while (argv[++count])
		if (ft_atolong(argv[count]) > INT_MAX || \
				ft_atolong(argv[count]) < INT_MIN)
			return (ft_putstr_fd("Error\n", 2), true);
	return (false);
}

bool	ft_sorted_max(char **argv)
{
	int	count;

	if (ft_check_max(argv))
		return (true);
	count = -1;
	while (argv[++count + 1])
		if (ft_atolong(argv[count]) > ft_atolong(argv[count + 1]))
			return (false);
	return (ft_putstr_fd("OK", 1), true);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;

	count = 0;
	while (s1[count] && s2[count] && s1[count] == s2[count])
		count ++;
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}

bool	ft_check_nbr(char **argv)
{
	int	count;
	int	index;

	count = -1;
	while (argv[++count])
	{
		index = -1;
		if (argv[count][0] == '-')
			index ++;
		while (argv[count][++index])
			if (!ft_isdigit(argv[count][index]))
				return (ft_putstr_fd("Error\n", 2), false);
		index = -1;
		while (argv[++index])
			if (count != index && !ft_strcmp(argv[count], argv[index]))
				return (ft_putstr_fd("Error\n", 2), false);
	}
	return (true);
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
	return (stack_a);
}

void	ft_free_op(char **list_op)
{
	int	count;

	count = -1;
	while (list_op[++count])
		free(list_op[count]);
	free(list_op);
}

bool	ft_check_op(char *op)
{
	if (!ft_strnstr("sasbssrarbrrrrarrbrrrpbpa", op, 25))
	{
		ft_putstr_fd("Error\n", 2);
		return (false);
	}
	return (true);
}

char	**ft_operation(void)
{
	char	*tmp;
	char	*str_op;
	char	**list_op;
	int		count;

	str_op = NULL;
	tmp = get_next_line(0);
	while (tmp)
	{
		str_op = ft_strjoin_free(str_op, tmp);
		free(tmp);
		tmp = get_next_line(0);
	}
	list_op = ft_split(str_op, '\n');
	free(str_op);
	count = -1;
	while (list_op[++count])
		if (!ft_check_op(list_op[count]))
			return (ft_free_op(list_op), NULL);
	return (list_op);
}

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

void	ft_check_input(char **argv)
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
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	else
		ft_check_input(&argv[1]);
	return (0);
}
