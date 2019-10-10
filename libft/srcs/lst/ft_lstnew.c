/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:04:37 by wta               #+#    #+#             */
/*   Updated: 2019/03/20 16:47:00 by williamta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	if ((node = (t_list*)malloc(sizeof(t_list))) != NULL)
	{
		if (content != NULL && (node->content = malloc(content_size)) != NULL)
		{
			ft_memcpy(node->content, content, content_size);
			node->content_size = content_size;
		}
		else
		{
			node->content = NULL;
			node->content_size = 0;
		}
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}
