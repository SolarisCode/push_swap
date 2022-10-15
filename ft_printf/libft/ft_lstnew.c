/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:41:36 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/16 00:12:28 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int *num)
{
	t_list	*new;

	if (!num)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->num = num;
	new->next = NULL;
	return (new);
}
