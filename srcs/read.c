/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:22:18 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 15:08:08 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_ssl.h"
#include "md5.h"

void		ft_ssl_string(t_hash *hash_env, char *str)
{
	size_t	i;

	hash_env->init_cmd(hash_env);
	hash_env->data_len = ft_strlen(str);
	ft_bzero(&hash_env->d_buffer, sizeof(t_digest_buffer));
	i = process_buffer(hash_env, &hash_env->d_buffer, (uint8_t*)str, hash_env->data_len);
	process_round(hash_env, i, hash_env->data_len, (uint8_t*)str);
	end_digest(hash_env);
	ft_ssl_get_result(hash_env);
}

void		ft_ssl_get_result(t_hash *hash_env)
{
	uint8_t	*ptr;
	int		i;

	i = -1;
	while (hash_env->big_endian && ++i < 8)
		hash_env->result[i] = byte_swap32(hash_env->result[i]);
	ptr = (uint8_t*)hash_env->result;
	i = 0;
	while (i < hash_env->output_size - 1)
	{
		byte_to_hexa(&hash_env->output[i], ptr[i / 2]);
		i += 2;
	}
	format_output(hash_env);
}

static void	process_read(t_env *env, int argc, char **args)
{
	t_hash	*hash_env;
	int		ac;

	ac = strings_array_len(args);
	if (ac && get_hash_cmd(env, argc, args))
	{
		hash_env = &env->hash_env;
		if (ac > 1)
			digest_files(hash_env, args + 1, ac - 1);
		else
			cmd_read(hash_env, STDIN_FILENO);
	}
	del_tab(args, ac);
}

int			ft_ssl_read(t_env *env, int argc)
{
	char	**args;
	char	*line;
	int		gnl_ret;

	ft_bzero(env, sizeof(env));
	ft_putstr("ft_ssl> ");
	if ((gnl_ret = get_next_line(STDIN_FILENO, &line)) == -1)
		error_panic();
	else if (gnl_ret == 0)
		exit(0);
	if ((args = ft_strsplit(line, ' ')) != NULL)
		process_read(env, argc, args);
	ft_strdel(&line);
	return (1);
}
