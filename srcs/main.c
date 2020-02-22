/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 14:59:01 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "sha.h"
#include "option.h"

static int	(*g_hash_cmds[])(t_hash *, char *) = {
	set_md5,
	set_sha1,
	set_sha224,
	set_sha256,
	NULL
};

static void	process_cli(t_hash *hash_env, int argc, char **argv)
{
	int	files_index;

	if (argc > 2)
	{
		hash_env->option.opt_count = argc - 2;
		hash_env->option.opt_list = &argv[2];
		files_index = manage_options(hash_env);
		hash_env->option.opts ^= (hash_env->option.opts & OPT_STRING);
		if (files_index != -1)
			digest_files(hash_env, &argv[files_index], argc - files_index);
		else if (option_has(&hash_env->option, OPT_REVERSE)
		|| option_has(&hash_env->option, OPT_QUIET))
			cmd_read(hash_env, STDIN_FILENO);
	}
	else if (argc == 2)
		cmd_read(hash_env, STDIN_FILENO);
}

int			get_hash_cmd(t_env *env, int argc, char *argv[])
{
	t_hash	*hash_env;
	size_t	i;

	hash_env = &env->hash_env;
	i = 0;
	ft_memcpy(env->cmd_name, argv[1], min(MAX_CMD_SIZE, ft_strlen(argv[1])));
	while (g_hash_cmds[i] && g_hash_cmds[i](hash_env, argv[1]) == 0)
		i++;
	if (!g_hash_cmds[i])
		return (0);
	hash_env->cmd_name = env->cmd_name;
	process_cli(hash_env, argc, argv);
	return (1);
}

int			main(int argc, char *argv[])
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (argc > 1)
	{
		if (!get_hash_cmd(&env, argc, argv))
			error_bad_cmd(&env);
	}
	else
	{
		while (1)
			ft_ssl_read(&env, argc);
	}
}
