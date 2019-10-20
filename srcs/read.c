/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:22:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/20 19:45:21 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_ssl.h"
#include "md5.h"

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

void	ft_ssl_get_result(t_env *env)
{
	uint8_t	*ptr;
	int		i;

	i = -1;
	while (env->big_endian && ++i < 8)
		env->result[i] = byte_swap32(env->result[i]);
	ptr = (uint8_t*)env->result;
	i = 0;
	while (i < env->output_size - 1)
	{
		byte_to_hexa(&env->output[i], ptr[i / 2]);
		i += 2;
	}
	format_output(env);
}

int		ft_ssl_read(t_env *env)
{
	char	**args;
	char	*line;
	int		gnl_ret;
	int		ac;

	ft_bzero(env, sizeof(t_env));
	ft_putstr("ft_ssl> ");
	gnl_ret = get_next_line(STDIN_FILENO, &line);
	if (gnl_ret == -1)
		return throw_error(env, ERR_PANIC);
	else if (gnl_ret == 0)
		exit(0);
	if ((args = ft_strsplit(line, ' ')) != NULL)
	{
		ac = strings_array_len(args);
		if (ac && get_cmd(env, args[0]))
		{
			if (ac > 1)
				digest_files(env, args + 1, ac - 1);
			else
				cmd_read(env, STDIN_FILENO);
		}
		else
			ft_putchar('\n');
		del_tab(args, ac);
	}
	ft_strdel(&line);
	return (1);
}
