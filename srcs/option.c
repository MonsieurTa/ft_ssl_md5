/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:13:52 by wta               #+#    #+#             */
/*   Updated: 2019/10/15 18:00:38 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "libft.h"
#include "ft_printf.h"
#include "option.h"
#include "md5.h"

static char g_opts[] = "pqrs";

int            apply_opt(t_env *env, char *c, char *opts)
{
    if (ft_strchr(g_opts, *c))
    {
        if (c == 'r' && !(*opts & OPT_PRINT)) {
            *opts |= OPT_REVERSE;
        }
        else if (c == 'q') {
            *opts = (*opts | OPT_QUIET) ^ (OPT_REVERSE);
        }
        else if (c == 'p') {
            *opts |= OPT_PRINT;
            ft_ssl_read(env, STDIN_FILENO);
        }
        else if (c == 's') {
            *opts |= OPT_STRING;
            return 0;
        }
        return 1;
    }
    return -1;
}

int             parse_option(t_env *env, int index)
{
    t_option    *opt;
    char        *c;
    int         ret;
    int         i;

    i = 0;
    opt = &env->option;
    if (opt->opt_list[index][i++] != '-')
        return 0;
    ret = 1;
    while ((c = &opt->opt_list[index][i]) != '\0' && ret)
    {
        env->option.curr_opt = c;
        if ((ret = apply_opt(env, c, &opt->opts)) == -1)
            new_error(env, ERR_ILLEGAL_OPT);
        i++;
    }
    return 1;
}

int             manage_options(t_env *env)
{
    int i;

    i = 0;
    while (i < env->option.opt_count && parse_option(env, i))
        i++;
    if (i < env->option.opt_count)
        return 2 + i;
    return -1;
}
