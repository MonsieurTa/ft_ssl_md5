/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:12:20 by wta               #+#    #+#             */
/*   Updated: 2020/02/28 17:43:29 by wta              ###   ########.fr       */
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

int		digest_file(t_hash *hash_env, char *filepath)
{
	int	fd;

	hash_env->input_src = filepath;
	if ((fd = open(filepath, O_RDONLY)) == -1)
		return (error_invalid_file(hash_env, ": No such file or directory\n"));
	if (read(fd, NULL, 0) < 0)
	{
		close(fd);
		return (error_invalid_file(hash_env, ": Invalid file\n"));
	}
	cmd_read(hash_env, fd);
	close(fd);
	return (1);
}

void	digest_files(t_hash *hash_env, char **filepaths, int index_max)
{
	int	i;

	i = 0;
	hash_env->option.opts |= OPT_ISFILE;
	while (i < index_max)
	{
		digest_file(hash_env, filepaths[i]);
		i++;
	}
}

int		digest_string(t_hash *hash_env, char *residual_opt, int index)
{
	static char	opt_error_str[] = ": option requires an argument -- ";

	if (*residual_opt == '\0' && index == hash_env->option.opt_count)
		return (error_illegal_opt(hash_env, opt_error_str));
	if (*residual_opt != '\0')
	{
		hash_env->input_src = residual_opt;
		ft_ssl_string(hash_env, residual_opt);
		format_output(hash_env);
		hash_env->option.residual_opt = 1;
		return (0);
	}
	hash_env->input_src = hash_env->option.opt_list[index];
	ft_ssl_string(hash_env, hash_env->option.opt_list[index]);
	format_output(hash_env);
	return (1);
}

void	end_digest(t_hash *hash_env)
{
	uint64_t	bitlen;
	uint64_t	*ptr;

	hash_env->d_buffer.buffer[hash_env->d_buffer.len] = 1 << 7;
	if (hash_env->big_endian)
		byte_swap32_buffer((uint32_t*)hash_env->d_buffer.buffer, 16);
	if (CHUNK_SIZE - hash_env->d_buffer.len <= 8)
	{
		hash_env->cmd(hash_env, (uint32_t*)hash_env->d_buffer.buffer);
		ft_bzero(&hash_env->d_buffer, sizeof(t_digest_buffer));
	}
	ptr = (uint64_t*)&hash_env->d_buffer.buffer[56];
	bitlen = hash_env->data_len * 8;
	if (hash_env->big_endian)
		bitlen = byte_swap64(bitlen);
	*ptr = bitlen;
	if (hash_env->big_endian)
		byte_swap32_buffer((uint32_t*)ptr, 2);
	hash_env->cmd(hash_env, (uint32_t*)hash_env->d_buffer.buffer);
}

void	process_round(t_hash *hash_env, size_t start, size_t end, uint8_t *data)
{
	while (start < end)
	{
		if (end - start < CHUNK_SIZE)
			fill_buffer(&hash_env->d_buffer, &data[start], end - start);
		else
		{
			if (hash_env->big_endian)
				byte_swap32_buffer((uint32_t*)&data[start], 16);
			hash_env->cmd(hash_env, (uint32_t*)&data[start]);
		}
		start += CHUNK_SIZE;
	}
}
