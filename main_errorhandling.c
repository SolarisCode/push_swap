/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_errorhandling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:49:04 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/18 01:05:08 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

bool	ft_check_max(char **argv, int *array)
{
	int		count;
	bool	max;

	count = -1;
	max = false;
	while (argv[++count])
	{
		if (argv[count][0] == '-' && array[count] > 0)
			max = true;
		else if (argv[count][0] != '-' && array[count] < 0)
			max = true;
	}
	free(array);
	if (max)
		ft_putstr_fd("Error\n", 1);
	return (max);
}

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
		array[count] = ft_atoi(argv[count]);
	count = 0;
	while(count <= size - 2 && array[count] < array[count + 1])
		count ++;
	if (count == size - 1)
		return (free(array), true);
	return (ft_check_max(argv, array));
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

int	ft_get_pivot(char **argv)
{
	int	size;
	int	count;
	int	*array;

	size = -1;
	while (argv[++size]);
	array = (int *)ft_calloc(size, sizeof(int));
	if (!array)
		return (0);
	count = -1;
	while (argv[++count])
		array[count] = ft_atoi(argv[count]);
	ft_quicksort(array, 0, size - 1);
	count = array[size / 2];
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

// void	ft_print_stack(t_list *stack)
// {
// 	t_list	*tmp;
//
// 	tmp = stack;
// 	ft_printf("Unsorted array\n");
// 	while (tmp)
// 	{
// 		ft_printf("%d ", tmp->num);
// 		tmp = tmp->next;
// 	}
// 	ft_printf("\n");
// }

void	ft_swap_nodes(t_list **stack, char *action)
{
	t_list	*head;

	head = (*stack)->next;
	(*stack)->next = (*stack)->next->next;
	head->next = *stack;
	*stack = head;
	ft_printf("%s\n", action);
}

void	ft_check_input(char **argv)
{
	t_list	*stack_a;
	int		pivot;

	if (!ft_check_nbr(argv) || ft_sorted_max(argv))
		return ;
	stack_a = ft_stack_a(argv);
	pivot = ft_get_pivot(argv);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	else
		ft_check_input(&argv[1]);
	return (0);
}
