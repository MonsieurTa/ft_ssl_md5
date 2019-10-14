/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:22:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 19:11:44 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"

#include "ft_printf.h"

size_t	process_digest_buffer(t_env *env, t_digest_buffer *d_buffer,
								uint8_t *r_buffer, size_t size)
{
	size_t	to_fill;

	if (d_buffer->len == 0)
		return 0;
	to_fill = 64 - d_buffer->len;
	if (to_fill > size)
		to_fill = size;
	ft_memcpy(d_buffer->buffer, r_buffer, to_fill);
	d_buffer->len += to_fill;
	if (d_buffer->len == 64)
	{
		env->cmd(env, (uint32_t*)d_buffer->buffer);
		d_buffer->len = 0;
	}
	return to_fill;
}

void	fill_digest_buffer(t_digest_buffer *d_buffer, char *r_buffer, size_t size)
{
	ft_memcpy(d_buffer->buffer, (void*)r_buffer, size);
	d_buffer->len = size;
}

void	end_digest(t_env *env)
{
	uint64_t	*ptr;

	env->d_buffer.buffer[env->d_buffer.len] = 1 << 7;
	if (64 - env->d_buffer.len <= 8)
	{
		env->cmd(env, (uint32_t*)env->d_buffer.buffer);
		env->d_buffer.len = 0;
	}
	ptr = (uint64_t*)&env->d_buffer.buffer[56];
	*ptr = env->data_len * 8;
	env->cmd(env, (uint32_t*)env->d_buffer.buffer);
}

void	ft_ssl_read(t_env *env, int fd)
{
	char	read_buffer[READ_BUFFER_LEN + 1];
	size_t	read_res;
	size_t	i;

	env->init_cmd(&env->tool);
	env->data_len = 0;
	ft_bzero(&env->d_buffer, sizeof(t_digest_buffer));
	ft_bzero(read_buffer, READ_BUFFER_LEN + 1);
	while ((read_res = read(fd, read_buffer, READ_BUFFER_LEN)) > 0)
	{
		env->data_len += read_res;
		read_buffer[read_res] = '\0';
		i = process_digest_buffer(env, &env->d_buffer, (uint8_t*)read_buffer, read_res);
		while (i < read_res)
		{
			if (read_res - i < 64)
				fill_digest_buffer(&env->d_buffer, &read_buffer[i], read_res - i);
			else
				env->cmd(env, (uint32_t*)&read_buffer[i]);
			i += 64;
		}
	}
	end_digest(env);
}