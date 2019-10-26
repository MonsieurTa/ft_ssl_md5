/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:12:20 by wta               #+#    #+#             */
/*   Updated: 2019/10/26 14:44:12 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ssl.h"
#include "option.h"
#include "md5.h"

int		digest_file(t_env *env, char *filepath)
{
	int	fd;

	env->input_src = filepath;
	if ((fd = open(filepath, O_RDONLY)) == -1)
		return (throw_error(env, ERR_MISSING));
	if (read(fd, NULL, 0) < 0)
		return (throw_error(env, ERR_INVALID_FILE));
	cmd_read(env, fd);
	close(fd);
	return (1);
}

void	digest_files(t_env *env, char **filepaths, int index_max)
{
	int	i;

	i = 0;
	env->option.opts |= OPT_ISFILE;
	while (i < index_max)
	{
		digest_file(env, filepaths[i]);
		i++;
	}
}

int		digest_string(t_env *env, char *residual_opt, int index)
{
	if (*residual_opt == '\0' && index == env->option.opt_count)
		return (throw_error(env, ERR_OPT_REQ_ARG));
	if (*residual_opt != '\0')
	{
		env->input_src = residual_opt;
		ft_ssl_string(env, residual_opt);
		env->option.residual_opt = 1;
		return (0);
	}
	env->input_src = env->option.opt_list[index];
	ft_ssl_string(env, env->option.opt_list[index]);
	return (1);
}

void	end_digest(t_env *env)
{
	uint64_t	bitlen;
	uint64_t	*ptr;

	env->d_buffer.buffer[env->d_buffer.len] = 1 << 7;
	if (env->big_endian)
		byte_swap32_buffer((uint32_t*)env->d_buffer.buffer, 16);
	if (CHUNK_SIZE - env->d_buffer.len <= 8)
	{
		env->cmd(env, (uint32_t*)env->d_buffer.buffer);
		ft_bzero(&env->d_buffer, sizeof(t_digest_buffer));
	}
	ptr = (uint64_t*)&env->d_buffer.buffer[56];
	bitlen = env->data_len * 8;
	if (env->big_endian)
		bitlen = byte_swap64(bitlen);
	*ptr = bitlen;
	if (env->big_endian)
		byte_swap32_buffer((uint32_t*)ptr, 2);
	env->cmd(env, (uint32_t*)env->d_buffer.buffer);
}

void	process_round(t_env *env, size_t start, size_t end, uint8_t *data)
{
	while (start < end)
	{
		if (end - start < CHUNK_SIZE)
			fill_buffer(&env->d_buffer, &data[start], end - start);
		else
		{
			if (env->big_endian)
				byte_swap32_buffer((uint32_t*)&data[start], 16);
			env->cmd(env, (uint32_t*)&data[start]);
		}
		start += CHUNK_SIZE;
	}
}
