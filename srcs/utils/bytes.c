/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:00:43 by wta               #+#    #+#             */
/*   Updated: 2019/10/18 14:58:49 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

uint32_t	byte_swap32(uint32_t x)
{
	return (((x >> 24) & 0xff) | (((x >> 16) & 0xff) << 8)
	| ((x >> 8) & 0xff) << 16 | (x & 0xff) << 24);
}

uint64_t	byte_swap64(uint64_t x)
{
	return ((x & 0x00000000000000FFUL) << 56 | (x & 0x000000000000FF00UL) << 40
	| (x & 0x0000000000FF0000UL) << 24 | (x & 0x00000000FF000000UL) << 8
	| (x & 0x000000FF00000000UL) >> 8 | (x & 0x0000FF0000000000UL) >> 24
	| (x & 0x00FF000000000000UL) >> 40 | (x & 0xFF00000000000000UL) >> 56);
}

void		byte_to_hexa(char *dst, uint8_t byte)
{
	dst[0] = "0123456789abcdef"[byte >> 4];
	dst[1] = "0123456789abcdef"[byte & 0xf];
}

void		byte_swap32_buffer(uint32_t *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		buffer[i] = byte_swap32(buffer[i]);
		i++;
	}
}
