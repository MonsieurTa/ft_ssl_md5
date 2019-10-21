/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:44:59 by wta               #+#    #+#             */
/*   Updated: 2019/10/21 11:48:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

size_t	process_buffer(t_env *env, t_digest_buffer *d_buffer,
								uint8_t *r_buffer, size_t size)
{
	size_t	to_fill;

	if (d_buffer->len == 0)
		return (0);
	to_fill = CHUNK_SIZE - d_buffer->len;
	if (to_fill > size)
		to_fill = size;
	ft_memcpy(&d_buffer->buffer[d_buffer->len], r_buffer, to_fill);
	d_buffer->len += to_fill;
	if (d_buffer->len == CHUNK_SIZE)
	{
		if (env->big_endian)
			byte_swap32_buffer((uint32_t*)d_buffer->buffer, 16);
		env->cmd(env, (uint32_t*)d_buffer->buffer);
		ft_bzero(d_buffer, sizeof(t_digest_buffer));
	}
	return (to_fill);
}

void	fill_buffer(t_digest_buffer *d_buffer, uint8_t *r_buffer, size_t size)
{
	ft_memcpy(d_buffer->buffer, (void*)r_buffer, size);
	d_buffer->len = size;
}
