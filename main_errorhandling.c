/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_errorhandling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:49:04 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/22 02:59:18 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "ft_printf/ft_printf_bonus.h"
#include "ft_printf/libft/libft.h"
#include <stdbool.h>

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
		if (ft_atolong(argv[count]) > INT_MAX || ft_atolong(argv[count]) < INT_MIN)
		{
			ft_putstr_fd("Error\n", 1);
			return (free(array), true);
		}
		else
			array[count] = (int)ft_atolong(argv[count]);
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

int	*ft_get_index(t_list *stack)
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
	return (array);
}

int	ft_find_index(int *array, int num, int end)
{
	int		mid;
	int		low;

	low = 0;
	mid = 0;
	while (end >= 1)
	{
		mid = (end + low) / 2;
		if (num == array[mid])
			return (mid);
		else if (num < array[mid])
			end = mid;
		else
			low = mid + 1;
	}
	return (mid);
}

void	ft_set_index(t_list *stack, int *array)
{
	t_list	*tmp;
	int		size;

	size = ft_lstsize(stack);
	tmp = stack;
	while (tmp)
	{
		tmp->index = ft_find_index(array, tmp->num, size - 1);
		tmp = tmp->next;
	}
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

t_list	*ft_stack_a(char **argv)
{
	t_list	*stack_a;
	int		*array;
	int		count;

	count = 0;
	stack_a = ft_lstnew((int)ft_atolong(argv[0]));
	while (argv[++count])
		ft_lstadd_back(&stack_a, ft_lstnew((int)ft_atolong(argv[count])));
	array = ft_get_index(stack_a);
	ft_set_index(stack_a, array);
	free(array);
	return (stack_a);
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
	int		top;
	int		bottom;

	top = ft_top_small(*stack_a, pivot);
	bottom = ft_bottom_small(*stack_a, pivot);
	if ((top < 0 && bottom < 0) || !ft_check_smaller(*stack_a, pivot))
		return ;
	ft_push_b(stack_a, stack_b, top, bottom);
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

int	ft_bottom_index(t_list *stack, int index)
{
	t_list	*tmp;
	int		bottom;

	tmp = ft_lstlast(stack);
	bottom = -1;
	while (tmp)
	{
		bottom ++;
		if (tmp->index == index)
			return (bottom);
		tmp = tmp->prev;
	}
	return (-1);
}

int	ft_top_index(t_list *stack, int index)
{
	t_list	*tmp;
	int		top;

	tmp = stack;
	top = -1;
	while (tmp)
	{
		top ++;
		if (tmp->index == index)
			return (top);
		tmp = tmp->next;
	}
	return (-1);
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

void	ft_sort_remain(t_list **stack)
{
	t_list	*head;

	head = *stack;
	if (head->num > (*stack)->next->num)
	{
		ft_printf("sa\n");
		head = (*stack)->next;
		head->prev = NULL;
		head->next = *stack;
		(*stack)->prev = head;
		(*stack)->next = NULL;
		*stack = head;
	}
}

void	ft_check_input(char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	if (!ft_check_nbr(argv) || ft_sorted_max(argv))
		return ;
	stack_a = ft_stack_a(argv);
	stack_b = NULL;
	stack_b = ft_stack_b(&stack_a, &stack_b);
	ft_sort_remain(&stack_a);
	ft_sort_stack(&stack_a, &stack_b);
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
