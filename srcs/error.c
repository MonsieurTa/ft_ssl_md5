/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:59:52 by wta               #+#    #+#             */
/*   Updated: 2019/10/15 14:41:38 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_ssl.h"
#include "libft.h"

static char	*g_usage = "usage: ./ft_ssl [md5 | sha256] [-prq] [-s string] [files ...]\n";

void	error_bad_cmd(t_env *env)
{
	write(STDERR_FILENO, "ft_ssl:Error: '", 15);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, "' is an invalid command.\n\n", 24);
	write(STDERR_FILENO, "Message digest commands\nmd5\nsha256\n\n", 40);
}

void	error_illegal_opt(t_env *env)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, ": illegal option -- ", 20);
	write(STDERR_FILENO, &env->option.curr_opt, 1);
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, g_usage, ft_strlen(g_usage));
}

void	error_missing(t_env *env)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, env->curr_filepath, ft_strlen(env->curr_filepath));
	write(STDERR_FILENO, ": No such file or directory", 27);
}

void	error_invalid_file(t_env *env)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, env->cmd_name, ft_strlen(env->cmd_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, env->curr_filepath, ft_strlen(env->curr_filepath));
	write(STDERR_FILENO, ": Invalid file", 27);
}

void	new_error(t_env *env, int err_code)
{
	if (err_code == ERR_BAD_CMD)
		error_bad_cmd(env);
	else if (err_code == ERR_USAGE)
		write(STDERR_FILENO, g_usage, ft_strlen(g_usage));
	else if (err_code == ERR_ILLEGAL_OPT)
		error_illegal_opt(env);
	else if (err_code == ERR_MISSING)
		error_missing(env);
	else if (err_code == ERR_INVALID_FILE)
		error_invalid_file(env);
	exit(0);
}