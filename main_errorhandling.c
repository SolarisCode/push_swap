/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_errorhandling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:49:04 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/20 21:43:50 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "ft_printf/ft_printf_bonus.h"
#include "ft_printf/libft/libft.h"
#include <stdbool.h>

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
				return (ft_putstr_fd("Error\n", 1), false);
		index = -1;
		while (argv[++index])
			if (count != index && !ft_strcmp(argv[count], argv[index]))
					return (ft_putstr_fd("Error\n", 1), false);
	}
	return (true);
}

// bool	ft_check_max(char **argv, int *array)
// {
// 	int		count;
// 	bool	max;
//
// 	count = -1;
// 	max = false;
// 	while (argv[++count])
// 	{
// 		if (argv[count][0] == '-' && array[count] > 0)
// 			max = true;
// 		else if (argv[count][0] != '-' && array[count] < 0)
// 			max = true;
// 	}
// 	free(array);
// 	if (max)
// 		ft_putstr_fd("Error\n", 1);
// 	return (max);
// }

bool	ft_sorted_max(char **argv)
{
	int	size;
	int	count;
	int	*array;

	size = -1;
	while (argv[++size]);
	array = (int *)ft_calloc(size, sizeof(int));
	if (!array)
		return (NULL);
	count = -1;
	while (argv[++count])
		if (ft_atoi(argv[count]) > INT_MAX || ft_atoi(argv[count]) < INT_MIN)
		{
			ft_putstr_fd("Error\n", 1);
			return (free(array), true);
		}
		else
			array[count] = (int)ft_atoi(argv[count]);
	count = 0;
	while(count <= size - 2 && array[count] < array[count + 1])
		count ++;
	if (count == size - 1)
		return (free(array), true);
	return (false);
}

void	ft_swap(int *array, int x, int y)
{
	int	tmp;

	tmp = array[x];
	array[x] = array[y];
	array[y] = tmp;
}

int	ft_partition(int *array, int start, int end)
{
	int	pindex;
	int	pivot;

	pivot = array[end];
	pindex = start;
	while (start < end)
	{
		if (array[start] < pivot)
		{
			ft_swap(array, start, pindex);
			pindex ++;
		}
		start ++;
	}
	ft_swap(array, pindex, end);
	return (pindex);
}

void	ft_quicksort(int *array, int start, int end)
{
	int	pindex;

	if (start >= end)
		return ;
	pindex = ft_partition(array, start, end);
	ft_quicksort(array, start, pindex - 1);
	ft_quicksort(array, pindex + 1, end);
}

int	ft_get_median(int *array, int size)
{
	int	count;
	int	diff[2];
	int	median;

	median = (array[0] + array[size / 2] + array[size - 1]) / 3;
	diff[0] = median - array[0];
	if (median - array[0] < 0)
		diff[0] *= -1;
	diff[1] = 0;
	count = 1;
	ft_printf("Median: %d\n", median);
	while (count < size && median > array[count])
	{
		if (diff[0] > median - array[count])
		{
			diff[0] = median - array[count];
			if (median - array[count] < 0)
				diff[0] *= -1;
			diff[1] = count;
		}
		count ++;
	}
	return (array[diff[1]]);
}

int	ft_get_pivot(t_list *stack)
{
	t_list	*tmp;
	int		*array;
	int		size;
	int		count;

	size = ft_lstsize(stack);
	array = (int *)ft_calloc(size, sizeof(int));
	if (!array)
		return (0);
	tmp = stack;
	count = 0;
	while (tmp)
	{
		array[count] = tmp->num;
		tmp = tmp->next;
		count ++;
	}
	ft_quicksort(array, 0, size - 1);
	count = array[size / 2];
	// count = ft_get_median(array, size);
	free(array);
	return (count);
}

t_list	*ft_stack_a(char **argv)
{
	t_list	*stack_a;
	int		count;

	count = 0;
	stack_a = ft_lstnew(ft_atoi(argv[0]));
	while (argv[++count])
		ft_lstadd_back(&stack_a, ft_lstnew(ft_atoi(argv[count])));
	return (stack_a);
}

void	ft_print_stack(t_list *stack)
{
	t_list	*tmp;

	tmp = stack;
	ft_printf("Unsorted array\n");
	while (tmp)
	{
		ft_printf("%d ", tmp->num);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

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
		tmp = *src;
		*src = (*src)->next;
		(*src)->prev = NULL;
		ft_printf("pb\n");
		free(tmp);
		return ;
	}
	(*dst)->prev = *src;
	*src = (*src)->next;
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
	(*stack)->next->prev = (*stack);
	(*stack)->prev = head;
	head->next = *stack;
	head->prev = NULL;
	*stack = head;
	ft_printf("%s\n", action);
}

void	ft_push_b(t_list **stack_a, t_list **stack_b, int down, int up)
{
	// ft_printf("Down: %d\nUp: %d\n", down , up);
	if (down < 0 || up < 0)
			return ;
	else if (down == 0)
		ft_push_node(stack_a, stack_b, "pb");
	else if (down == 1)
	{
		ft_swap_nodes(stack_a, "sa");
		ft_push_node(stack_a, stack_b, "pb");
	}
	else if (down <= up)
	{
		ft_rotate_nodes(stack_a, "ra");
		ft_push_b(stack_a, stack_b, down - 1, up + 1);
	}
	else
	{
		ft_reverse_rotate(stack_a, "rra");
		if (up - 1 < 0)
			ft_push_node(stack_a, stack_b, "pb");
		ft_push_b(stack_a, stack_b, down + 1, up - 1);
	}
}

// void	ft_b_to_a(t_list **stack_a, t_list **stack_b)
// {
// 	t_list	*tmp;
// 	int		pivot;
// 	int		down;
// 	int		up;
//
// 	down = 0;
// 	up = 0;
// 	if (!*stack_b)
// 		return ;
// 	pivot = ft_get_pivot(*stack_a);
// 	tmp = *stack_a;
// 	while (tmp && tmp->num > pivot)
// 	{
// 		tmp = tmp->next;
// 		down ++;
// 	}
// 	tmp = ft_lstlast(*stack_a);
// 	while (tmp && tmp->num > pivot)
// 	{
// 		tmp = tmp->prev;
// 		up ++;
// 	}
// 	ft_push_b(stack_a, stack_b, down, up);
// 	ft_stack_b(stack_a, stack_b);
// 	return (*stack_b);
// }

void	ft_set_groups(t_list **stack_b, int group)
{
	t_list *tmp;

	tmp = *stack_b;
	while (tmp)
	{
		if (tmp->group == 0)
			tmp->group = group;
		tmp = tmp->next;
	}
}

bool	ft_check_smaller(t_list *stack, int pivot)
{
	t_list	*tmp;
	bool	found;

	found = false;
	tmp = stack;
	while (tmp)
	{
		if (tmp->num < pivot)
			found = true;
		tmp = tmp->next;
	}
	return (found);
}

int	ft_bottom_small(t_list *stack, int pivot)
{
	t_list	*tmp;
	int		bottom;

	tmp = ft_lstlast(stack);
	bottom = -1;
	while (tmp)
	{
		bottom ++;
		if (tmp->num < pivot)
			return (bottom);
		tmp = tmp->prev;
	}
	return (-1);
}

int	ft_top_small(t_list *stack, int pivot)
{
	t_list	*tmp;
	int		top;

	tmp = stack;
	top = -1;
	while (tmp)
	{
		top ++;
		if (tmp->num < pivot)
			return (top);
		tmp = tmp->next;
	}
	return (-1);
}

void	ft_create_groups(t_list **stack_a, t_list **stack_b, int pivot)
{
	int		down;
	int		up;

	down = ft_top_small(*stack_a, pivot);
	up = ft_bottom_small(*stack_a, pivot);
	if ((down < 0 && up < 0) || !ft_check_smaller(*stack_a, pivot))
		return ;
	ft_push_b(stack_a, stack_b, down, up);
	ft_create_groups(stack_a, stack_b, pivot);
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

t_list	*ft_stack_b(t_list **stack_a, t_list **stack_b)
{
	static int	group;
	int			pivot;

	if (ft_lstsize(*stack_a) < 3)
		return (*stack_b);
	pivot = ft_get_pivot(*stack_a);
	// ft_printf("Pivot: %d\n", pivot);
	if (!ft_check_smaller(*stack_a, pivot) && !(ft_lstsize(*stack_a) < 3))
	{
		ft_send_pivot(stack_a, stack_b, pivot);
		return (*stack_b);
	}
	ft_create_groups(stack_a, stack_b, pivot);
	ft_set_groups(stack_b, ++group);
	// ft_print_stack(*stack_b);
	ft_stack_b(stack_a, stack_b);
	return (*stack_b);
}

void	ft_check_input(char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	if (!ft_check_nbr(argv) || ft_sorted_max(argv))
		return ;
	stack_a = ft_stack_a(argv);
	// ft_print_stack(stack_a);
	// ft_reverse_rotate(&stack_a, "rra");
	// ft_rotate_nodes(&stack_a, "ra");
	// ft_swap_nodes(&stack_a, "sa");
	// ft_print_stack(stack_a);
	stack_b = NULL;
	stack_b = ft_stack_b(&stack_a, &stack_b);
	// ft_print_stack(stack_a);
	// ft_print_stack(stack_b);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	else
		ft_check_input(&argv[1]);
	return (0);
}
