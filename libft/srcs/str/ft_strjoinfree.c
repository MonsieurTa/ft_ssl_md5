/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:42:55 by wta               #+#    #+#             */
/*   Updated: 2019/03/19 22:45:22 by williamta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoinfree(char const *s1, char const *s2)
{
	char	*new;

	new = NULL;
	if (s1 && s2)
	{
		if (!(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		new = ft_strcpy(new, s1);
		new = ft_strcat(new, s2);
		ft_strdel((char**)&s1);
		ft_strdel((char**)&s2);
		return (new);
	}
	return (NULL);
}
