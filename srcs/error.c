/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:59:52 by wta               #+#    #+#             */
/*   Updated: 2019/10/20 18:32:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_ssl.h"
#include "libft.h"

static char	*g_usage = "usage: ./ft_ssl [md5 | sha256]	\
[-prq] [-s string] [files ...]\n";

static void	error_bad_cmd(t_env *env)
{
	write(STDERR_FILENO, "ft_ssl:Error: '", 15);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, "' is an invalid command.\n\n", 26);
	write(STDERR_FILENO, "Message digest commands:\n"
	"md5\n"
	"sha1\n"
	"sha224\n"
	"sha256\n\n", 49);
}

static void	error_illegal_opt(t_env *env, char *msg)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, &env->option.curr_opt, 1);
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, g_usage, ft_strlen(g_usage));
	ft_memdel((void**)&env->input);
	exit(0);
}

static void	error_invalid_file(t_env *env, char *msg)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, env->input_src, ft_strlen(env->input_src));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	ft_memdel((void**)&env->input);
}

static void	error_panic(t_env *env)
{
	char	msg[] = "Something went wrong: Clean exit...";
	write(STDERR_FILENO, "ft_ssl:PANIC: ", 8);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	ft_memdel((void**)&env->input);
	exit(0);
}

int			throw_error(t_env *env, int err_code)
{
	if (err_code == ERR_BAD_CMD)
		error_bad_cmd(env);
	else if (err_code == ERR_PANIC)
		error_panic(env);
	else if (err_code == ERR_USAGE)
		write(STDERR_FILENO, g_usage, ft_strlen(g_usage));
	else if (err_code == ERR_ILLEGAL_OPT)
		error_illegal_opt(env, ": illegal option -- ");
	else if (err_code == ERR_OPT_REQ_ARG)
		error_illegal_opt(env, ": option requires an argument -- ");
	else if (err_code == ERR_MISSING)
		error_invalid_file(env, ": No such file or directory\n");
	else if (err_code == ERR_INVALID_FILE)
		error_invalid_file(env, ": Invalid file\n");
	return (0);
}
