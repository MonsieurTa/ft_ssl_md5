/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamta <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:23:19 by williamta         #+#    #+#             */
/*   Updated: 2019/03/20 17:51:59 by williamta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_listdel(t_list_info *list)
{
	t_list	*node;
	t_list	*tmp;

	node = list->head;
	if (node != NULL)
	{
		list->head = NULL;
		list->tail = NULL;
		while (node != NULL)
		{
			tmp = node;
			node = node->next;
			free(tmp->content);
			free(tmp);
		}
	}
}
