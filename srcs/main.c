/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/20 18:27:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "sha.h"
#include "option.h"

static int	ft_ssl_assign_cmd(t_env *env, void (*init)(t_env *),
					void (*cmd)(t_env *, uint32_t *))
{
	env->cmd = cmd;
	env->init_cmd = init;
	return 1;
}

static void	process_cli(t_env *env, int ac, char **av)
{
	int	files_index;

	if (ac > 2)
	{
		env->option.opt_count = ac - 2;
		env->option.opt_list = &av[2];
		files_index = manage_options(env);
		env->option.opts ^= (env->option.opts & OPT_STRING);
		if (files_index != -1)
			digest_files(env, &av[files_index], ac - files_index);
	}
	else if (ac == 2)
		cmd_read(env, STDIN_FILENO);
}

int			get_cmd(t_env *env, char *str)
{
	ft_memcpy(env->cmd_name, str, MIN(MAX_CMD_SIZE, ft_strlen(str)));
	if (ft_strequ(str, "md5"))
		return ft_ssl_assign_cmd(env, md5_init, md5);
	else if (ft_strequ(str, "sha256"))
		return ft_ssl_assign_cmd(env, sha256_init, sha256);
	else if (ft_strequ(str, "sha1"))
		return ft_ssl_assign_cmd(env, sha1_init, sha1);
	else if (ft_strequ(str, "sha224"))
		return ft_ssl_assign_cmd(env, sha224_init, sha256);
	return (throw_error(env, ERR_BAD_CMD));
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (ac > 1)
	{
		if (get_cmd(&env, av[1]))
			process_cli(&env, ac, av);
	}
	else
	{
		while (1)
			ft_ssl_read(&env);
	}
}
