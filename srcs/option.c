/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:13:52 by wta               #+#    #+#             */
/*   Updated: 2019/10/26 14:21:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "libft.h"
#include "option.h"
#include "md5.h"

static char g_opts[] = "pqrs";

static int	apply_option(t_env *env, char c, char *opts)
{
	if (ft_strchr(g_opts, c))
	{
		if (c == 'r' && !(*opts & OPT_PRINT))
			*opts |= OPT_REVERSE;
		else if (c == 'q')
			*opts = (*opts | OPT_QUIET) ^ (OPT_REVERSE);
		else if (c == 'p')
		{
			*opts |= OPT_PRINT;
			cmd_read(env, STDIN_FILENO);
		}
		else if (c == 's')
			*opts |= OPT_STRING;
		return (1);
	}
	return (-1);
}

static int	parse_option(t_env *env, int idx)
{
	t_option	*opt;
	char		c;
	int			ret;
	int			i;
	int			len;

	i = 0;
	opt = &env->option;
	len = ft_strlen(opt->opt_list[idx]);
	if (opt->opt_list[idx][i++] != '-' || len == 1)
		return (0);
	ret = 1;
	while ((c = opt->opt_list[idx][i]) != '\0' && ret)
	{
		opt->curr_opt = c;
		if ((ret = apply_option(env, c, &opt->opts)) == -1)
			throw_error(env, ERR_ILLEGAL_OPT);
		if (option_has(opt, OPT_STRING))
			return (digest_string(env, &opt->opt_list[idx][i + 1], idx + 1));
		i++;
	}
	return (1);
}

int			manage_options(t_env *env)
{
	int i;

	i = 0;
	while (i < env->option.opt_count && parse_option(env, i))
		i++;
	if (i < env->option.opt_count)
		return (2 + i + option_has(&env->option, OPT_STRING));
	return (-1);
}

int			option_has(t_option *option, int opt)
{
	return ((option->opts & opt) != 0);
}
