/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:36:29 by wta               #+#    #+#             */
/*   Updated: 2019/10/20 17:37:18 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

void	cmd_read(t_env *env, int fd)
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
