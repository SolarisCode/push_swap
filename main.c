/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:38:17 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:29:58 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int	ft_get_median(int *array, int size)
// {
// 	int	count;
// 	int	diff[2];
// 	int	median;
//
// 	median = (array[0] + array[size / 2] + array[size - 1]) / 3;
// 	diff[0] = median - array[0];
// 	if (median - array[0] < 0)
// 		diff[0] *= -1;
// 	diff[1] = 0;
// 	count = 1;
// 	ft_printf("Median: %d\n", median);
// 	while (count < size && median > array[count])
// 	{
// 		if (diff[0] > median - array[count])
// 		{
// 			diff[0] = median - array[count];
// 			if (median - array[count] < 0)
// 				diff[0] *= -1;
// 			diff[1] = count;
// 		}
// 		count ++;
// 	}
// 	return (array[diff[1]]);
// }
//
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

void	ft_swap(int *array, int x, int y)
{
	int	tmp;

	tmp = array[x];
	array[x] = array[y];
	array[y] = tmp;
}

void	ft_insert(int *array, int size, int index)
{
	int	key;
	int	ivalue;

	key = array[index];
	ivalue = index - 1;
	while (ivalue >= 0 && array[ivalue] > key)
	{
		array[ivalue + 1] = array[ivalue];
		ivalue --;
	}
	array[ivalue + 1] = key;
}

void	ft_instsort(int *array, int size)
{
	int	count;

	count = 1;
	while (count < size)
	{
		ft_insert(array, size, count);
		count ++;
	}
}

void	ft_bubble(int *array, int size)
{
	int	count;

	count = size - 1;
	while (count > 0)
	{
		if (array[count] < array[count - 1])
			ft_swap(array, count, count - 1);
		count --;
	}
}

void	ft_bblsort(int *array, int size)
{
	int	count;

	count = 0;
	while (count < size - 1)
	{
		ft_bubble(array, size);
		count ++;
	}
}

int	ft_smallest(int *array, int start, int end)
{
	int	index;
	int	count;

	index = start;
	count = index;
	while (index <= end)
	{
		if (array[index] < array[count])
			count = index;
		index ++;
	}
	return (count);
}

void	ft_selsort(int *array, int size)
{
	int	start;
	int	small;

	start = 0;
	while (start < size - 1)
	{
		small = ft_smallest(array, start, size - 1);
		ft_swap(array, start, small);
		start ++;
	}
}

void	ft_combine(int *array, int start, int mid, int end)
{
	int	icount;
	int	jcount;
	int	kcount;
	int	*buff;

	buff = (int *)calloc(end + 1, sizeof(int));
	printf("count: %d\n", end);
	kcount = start;
	while (kcount <= end)
	{
		buff[kcount] = array[kcount];
		kcount ++;
	}
	kcount = start;
	icount = start;
	jcount = mid + 1;
	while (icount <= mid && jcount <= end)
	{
		if (buff[icount] <= buff[jcount])
		{
			array[kcount] = buff[icount];
			icount ++;
		}
		else
		{
			array[kcount] = buff[jcount];
			jcount ++;
		}
		kcount ++;
	}
	while (icount <= mid)
	{
		array[kcount] = buff[icount];
		icount ++;
		kcount ++;
	}
	while (jcount <= end)
	{
		array[kcount] = buff[jcount];
		jcount ++;
		kcount ++;
	}
	free(buff);
}

void	ft_mergsort(int *array, int start, int end)
{
	int	mid;

	if (start >= end)
		return ;
	mid = (start + end) / 2;
	ft_mergsort(array, start, mid);
	ft_mergsort(array, mid + 1, end);
	ft_combine(array, start, mid, end);
}

int	ft_partition(int *array, int start, int end)
{
	int	pivot;
	int	partindex;

	pivot = array[end];
	partindex = start;
	while (start < end)
	{
		if (array[start] < pivot)
		{
			ft_swap(array, start, partindex);
			partindex ++;
		}
		start ++;
	}
	ft_swap(array, partindex, end);
	return (partindex);
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

int	main(int argc, char *argv[])
{
	size_t	size;
	int		count;
	int		num;
	int		*array;

	count = 0;
	num = -1;
	while (argv[++count]);
	array = (int *)calloc(count - 1, sizeof(int));
	while (--count > 0)
		array[++num] = atoi(argv[count]);
	size = num + 1;
	printf("Unsorted Array\n");
	while (num >= 0)
	{
		printf("%d ", array[num]);
		num --;
	}
	printf("\n");
	// ft_selsort(array, size);
	// ft_bblsort(array, size);
	// ft_instsort(array, size);
	// ft_mergsort(array, 0, size - 1);
	ft_quicksort(array, 0, size - 1);
	num = 0;
	printf("Sorted Array\n");
	while (num < size)
	{
		printf("%d ", array[num]);
		num ++;
	}
	printf("\n");
	free(array);
	return (0);
}
