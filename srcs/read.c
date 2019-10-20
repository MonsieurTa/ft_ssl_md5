/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:22:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/21 12:13:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_ssl.h"
#include "md5.h"

void		ft_ssl_string(t_env *env, char *str)
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

void		ft_ssl_get_result(t_env *env)
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

static void	process_read(t_env *env, char **args)
{
	int	ac;

	ac = strings_array_len(args);
	if (ac && get_cmd(env, args[0]))
	{
		if (ac > 1)
			digest_files(env, args + 1, ac - 1);
		else
			cmd_read(env, STDIN_FILENO);
	}
	del_tab(args, ac);
}

int			ft_ssl_read(t_env *env)
{
	char	**args;
	char	*line;
	int		gnl_ret;

	ft_bzero(env, sizeof(t_env));
	ft_putstr("ft_ssl> ");
	if ((gnl_ret = get_next_line(STDIN_FILENO, &line)) == -1)
		return (throw_error(env, ERR_PANIC));
	else if (gnl_ret == 0)
		exit(0);
	if ((args = ft_strsplit(line, ' ')) != NULL)
		process_read(env, args);
	ft_strdel(&line);
	return (1);
}
