/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:08:53 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/01 18:23:47 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include "../ft_printf/ft_printf_bonus.h"
# include "../ft_printf/libft/libft.h"

/* checker_bonus.c */
bool	ft_sorted_stack(t_list *stack);
void	ft_free_stack(t_list **stack);
void	ft_check_execute(char **argv);
t_list	*ft_stack_a(char **argv);

/* utils_bonus.c */
int		ft_strcmp(const char *s1, const char *s2);
long	ft_atolong(const char *str);
void	ft_free_op(char **list_op);
bool	ft_check_op(char *op);

/* check_input_bonus.c */
bool	ft_check_max(char **argv);
bool	ft_sorted_max(char **argv);
bool	ft_check_nbr(char **argv);
char	**ft_operation(void);

/* operations_bonus.c */
void	ft_reverse_rotate(t_list **stack);
void	ft_rotate_nodes(t_list **stack);
void	ft_push_node(t_list **src, t_list **dst);
void	ft_swap_nodes(t_list **stack);

/* actions_bonus.c */
void	ft_double_action(t_list **stack_a, t_list **stack_b, char *action);
void	ft_actions(t_list **stack_a, t_list **stack_b, char **list_op);

#endif
