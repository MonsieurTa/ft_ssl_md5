/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushfront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:20:19 by wta               #+#    #+#             */
/*   Updated: 2019/03/20 17:50:37 by williamta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pushfront(t_list_info *list, t_list *node)
{
	if (node != NULL)
	{
		if (list->head == NULL && list->tail == NULL)
		{
			list->head = node;
			list->tail = node;
		}
		else
		{
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
	}
}
