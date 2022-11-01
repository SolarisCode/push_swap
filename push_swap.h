/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:05:37 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 19:25:40 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include "ft_printf/ft_printf_bonus.h"
# include "ft_printf/libft/libft.h"

/* push_swap.c */
t_list	*ft_stack_b(t_list **stack_a, t_list **stack_b);
void	ft_free_stack(t_list **stack);
void	ft_check_execute(char **argv);
t_list	*ft_stack_a(char **argv);

/* utils.c */
void	ft_quicksort(int *array, int start, int end);
int		ft_partition(int *array, int start, int end);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_swap(int *array, int x, int y);
long	ft_atolong(const char *str);

/* check_input.c */
bool	ft_check_nbr(char **argv);
bool	ft_check_max(char **argv);
bool	ft_sorted_max(char **argv);

/* operations.c */
void	ft_push_node(t_list **src, t_list **dst, char *action);
void	ft_reverse_rotate(t_list **stack, char *action);
void	ft_rotate_nodes(t_list **stack, char *action);
void	ft_swap_nodes(t_list **stack, char *action);

/* helper_funcs.c */
void	ft_set_groups(t_list **stack_b, int group);
bool	ft_check_smaller(t_list *stack, int pivot);
int		ft_get_pivot(t_list *stack);

/* indexing.c */
int		ft_find_index(int *array, int num, int end);
int		ft_bottom_index(t_list *stack, int index);
void	ft_set_index(t_list *stack, int *array);
int		ft_top_index(t_list *stack, int index);
void	ft_get_index(t_list *stack);

/* actions.c */
void	ft_push_b(t_list **stack_a, t_list **stack_b, int top, int bottom);
void	ft_push_a(t_list **stack_b, t_list **stack_a, int top, int bottom);
void	ft_send_pivot(t_list **stack_a, t_list **stack_b, int pivot);
int		ft_bottom_best(t_list *stack, int pivot, int flag);
int		ft_top_best(t_list *stack, int pivot, int flag);

/* small_stack.c */
void	ft_sort_five(t_list **stack_a, t_list **stack_b);
bool	ft_sorted_stack(t_list *stack);
void	ft_remain_five(t_list **stack);
void	ft_small_stack(char **argv);

/* sort_stack.c */
void	ft_create_groups(t_list **stack_a, t_list **stack_b, int pivot);
void	ft_sort_stack(t_list **stack_a, t_list **stack_b);
void	ft_sort_remain(t_list **stack, char *action);

#endif
