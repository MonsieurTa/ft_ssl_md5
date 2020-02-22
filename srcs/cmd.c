/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:36:29 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 14:40:14 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"

void	cmd_read(t_hash *hash_env, int fd)
{
	size_t	ret;
	size_t	i;

	hash_env->init_cmd(hash_env);
	hash_env->data_len = 0;
	ft_bzero(&hash_env->d_buffer, sizeof(t_digest_buffer));
	while ((ret = read(fd, hash_env->d_buffer.r_buffer, READ_BUFFER_LEN)) > 0)
	{
		hash_env->data_len += ret;
		hash_env->d_buffer.r_buffer[ret] = '\0';
		if (option_has(&hash_env->option, OPT_PRINT))
			write(STDOUT_FILENO, hash_env->d_buffer.r_buffer, ret);
		i = process_buffer(hash_env, &hash_env->d_buffer, hash_env->d_buffer.r_buffer, ret);
		process_round(hash_env, i, ret, hash_env->d_buffer.r_buffer);
	}
	end_digest(hash_env);
	ft_ssl_get_result(hash_env);
}
