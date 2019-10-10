/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 02:35:47 by wta               #+#    #+#             */
/*   Updated: 2019/05/15 23:11:43 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "stdint.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	uint8_t	*dest;
	uint8_t	*source;
	uint8_t	ref;

	ref = c;
	dest = (uint8_t*)dst;
	source = (uint8_t*)src;
	while (n--)
	{
		*dest++ = *source++;
		if (ref == *(source - 1))
			return (dest);
	}
	return (NULL);
}
