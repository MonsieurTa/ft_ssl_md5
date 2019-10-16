/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:00:43 by wta               #+#    #+#             */
/*   Updated: 2019/10/16 11:01:40 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

void		swap_byte(void *ptr, uint32_t size)
{
	uint32_t	low;
	uint8_t		tmp;
	uint8_t		*cptr;

	cptr = ptr;
	low = 0;
	while (low < size)
	{
		size--;
		tmp = cptr[size];
		cptr[size] = cptr[low];
		cptr[low] = tmp;
		low++;
	}
}

void		byte_to_hexa(char *dst, uint8_t byte)
{
	dst[0] = "0123456789abcdef"[byte >> 4];
	dst[1] = "0123456789abcdef"[byte & 0xf];
}
