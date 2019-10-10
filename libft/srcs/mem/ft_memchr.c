/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 02:57:20 by wta               #+#    #+#             */
/*   Updated: 2019/05/15 23:12:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*dst;

	dst = (const unsigned char*)s;
	while (n--)
		if (*dst++ == (unsigned char)c)
			return ((void*)dst - 1);
	return (NULL);
}
