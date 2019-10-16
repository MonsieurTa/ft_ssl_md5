/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:22:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/16 17:29:44 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"

size_t	process_buffer(t_env *env, t_digest_buffer *d_buffer,
								uint8_t *r_buffer, size_t size)
{
	size_t	to_fill;

	if (d_buffer->len == 0)
		return 0;
	to_fill = CHUNK_SIZE - d_buffer->len;
	if (to_fill > size)
		to_fill = size;
	ft_memcpy(&d_buffer->buffer[d_buffer->len], r_buffer, to_fill);
	d_buffer->len += to_fill;
	if (d_buffer->len == CHUNK_SIZE)
	{
		env->cmd(env, (uint32_t*)d_buffer->buffer);
		ft_bzero(d_buffer, sizeof(t_digest_buffer));
	}
	return to_fill;
}

void	fill_buffer(t_digest_buffer *d_buffer, uint8_t *r_buffer, size_t size)
{
	ft_memcpy(d_buffer->buffer, (void*)r_buffer, size);
	d_buffer->len = size;
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
		env->data_len += ret;
		env->d_buffer.r_buffer[ret] = '\0';
		if (option_has(&env->option, OPT_PRINT))
			track_input(env, env->d_buffer.r_buffer);
		i = process_buffer(env, &env->d_buffer, env->d_buffer.r_buffer, ret);
		process_round(env, i, ret, env->d_buffer.r_buffer);
	}
	end_digest(env);
	ft_ssl_get_result(env);
}

void	ft_ssl_string(t_env *env, char *str)
{
	size_t	i;

	env->init_cmd(env);
	env->data_len = ft_strlen(str);
	ft_bzero(&env->d_buffer, sizeof(t_digest_buffer));
	i = process_buffer(env, &env->d_buffer, (uint8_t*)str, env->data_len);
	process_round(env, i, env->data_len, (uint8_t*)str);
	end_digest(env);
	ft_ssl_get_result(env);
}
