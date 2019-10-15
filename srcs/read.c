/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:22:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/15 14:53:24 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"

#include "ft_printf.h"

size_t	process_buffer(t_env *env, t_digest_buffer *d_buffer,
								uint8_t *r_buffer, size_t size)
{
	size_t	to_fill;

	if (d_buffer->len == 0)
		return 0;
	to_fill = CHUNK_SIZE - d_buffer->len;
	if (to_fill > size)
		to_fill = size;
	ft_memcpy(d_buffer->buffer, r_buffer, to_fill);
	d_buffer->len += to_fill;
	if (d_buffer->len == CHUNK_SIZE)
	{
		env->cmd(env, (uint32_t*)d_buffer->buffer);
		d_buffer->len = 0;
	}
	return to_fill;
}

void	fill_buffer(t_digest_buffer *d_buffer, uint8_t *r_buffer, size_t size)
{
	ft_memcpy(d_buffer->buffer, (void*)r_buffer, size);
	d_buffer->len = size;
}

void	end_digest(t_env *env)
{
	uint64_t	*ptr;

	env->d_buffer.buffer[env->d_buffer.len] = 1 << 7;
	if (CHUNK_SIZE - env->d_buffer.len <= 8)
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
	size_t	ret;
	size_t	i;

	env->init_cmd(env);
	env->data_len = 0;
	ft_bzero(&env->d_buffer, sizeof(t_digest_buffer));
	while ((ret = read(fd, env->d_buffer.r_buffer, READ_BUFFER_LEN)) > 0)
	{
		if (env->option.opts & OPT_PRINT) {}
			// do smt
		env->data_len += ret;
		env->d_buffer.r_buffer[ret] = '\0';
		i = process_buffer(env, &env->d_buffer, env->d_buffer.r_buffer, ret);
		while (i < ret)
		{
			if (ret - i < CHUNK_SIZE)
				fill_buffer(&env->d_buffer, &env->d_buffer.r_buffer[i],
				ret - i);
			else
				env->cmd(env, (uint32_t*)&env->d_buffer.r_buffer[i]);
			i += CHUNK_SIZE;
		}
	}
	end_digest(env);
	ft_ssl_get_result(env);
}