/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:59:52 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 15:06:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_ssl.h"
#include "libft.h"

static char	*g_usage = "usage: ./ft_ssl [md5 | sha1 | sha224 | sha256]"
"[-prq] [-s string] [files ...]\n";

int			error_bad_cmd(t_env *env)
{
	write(STDERR_FILENO, "ft_ssl:Error: '", 15);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, "' is an invalid command.\n\n", 26);
	write(STDERR_FILENO, "Message digest commands:\n"
	"md5\n"
	"sha1\n"
	"sha224\n"
	"sha256\n\n", 49);
	return (-1);
}

int			error_illegal_opt(t_hash *hash_env, char *msg)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, hash_env->cmd_name, ft_strlen(hash_env->cmd_name));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, &hash_env->option.curr_opt, 1);
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, g_usage, ft_strlen(g_usage));
	exit(0);
}

int			error_invalid_file(t_hash *hash_env, char *msg)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, hash_env->cmd_name, ft_strlen(hash_env->cmd_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, hash_env->input_src, ft_strlen(hash_env->input_src));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (0);
}

void		error_panic(void)
{
	static char	msg[] = "Something went wrong: Clean exit...";

	write(STDERR_FILENO, "ft_ssl:PANIC: ", 14);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(0);
}

int			throw_hash_opt_error(t_hash *hash_env, int err_code)
{
	if (err_code == ERR_ILLEGAL_OPT)
		error_illegal_opt(hash_env, ": illegal option -- ");
	else if (err_code == ERR_OPT_REQ_ARG)
		error_illegal_opt(hash_env, ": option requires an argument -- ");
	return (0);
}
