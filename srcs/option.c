/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:13:52 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 17:17:00 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "libft.h"
#include "ft_printf.h"
#include "option.h"
#include "md5.h"

char    g_options[] = "pqrs";

int     parse_option(t_env *env, int index)
{
    t_option    *opt;
    char        c;
    int         i;

    i = 0;
    opt = &env->option;
    if (opt->opt_list[index][i++] != '-')
        return 0;
    while ((c = opt->opt_list[index][i]) != '\0')
    {
        if (c == 'q')
            opt->quiet |= 0x1;
        else if (c == 'r')
            opt->reverse |= 0x1;
        else if (c == 'p')
        {
            ft_ssl_read(env, STDIN_FILENO);
            md5_join_result(&env->tool, env);
            md5_get_result(env);
            ft_printf("%s\n", env->result);
        }
        else if (c == 's') {}
        i++;
        // else illegal option
    }
    return 1;
}

int    manage_options(t_env *env)
{
    int i;

    i = 0;
    while (i < env->option.opt_count && parse_option(env, i))
        i++;
    if (i < env->option.opt_count)
        return 2 + i;
    return -1;
}
