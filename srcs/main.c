/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/26 13:01:24 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "sha.h"
#include "option.h"

static int	(*g_cmds[])(t_env *, char *) = {
	set_md5,
	set_sha1,
	set_sha224,
	set_sha256,
	NULL
};

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
		else
			cmd_read(env, STDIN_FILENO);
	}
	else if (ac == 2)
		cmd_read(env, STDIN_FILENO);
}

int			get_cmd(t_env *env, char *name)
{
	size_t	i;

	i = 0;
	ft_memcpy(env->cmd_name, name, MIN(MAX_CMD_SIZE, ft_strlen(name)));
	while (g_cmds[i] && g_cmds[i](env, name) == 0)
		i++;
	if (!g_cmds[i])
		return (throw_error(env, ERR_BAD_CMD));
	return (1);
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
