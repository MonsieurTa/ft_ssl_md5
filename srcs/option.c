/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:13:52 by wta               #+#    #+#             */
/*   Updated: 2019/10/11 18:02:00 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "option.h"

char    g_options[] = "pqrs";

#include <stdio.h>

void    init_data(t_env *env)
{
    ft_memdel((void**)&env->data);
    env->data = (uint8_t*)ft_strnew(0);
    env->data_len = 0;
}

void    get_input(t_env *env)
{
    char    buffer[512 + 1];
    size_t  read_res;

    ft_bzero(buffer, 513);
    while ((read_res = read(1, buffer, 512)) > 0)
    {
        env->data = (uint8_t*)ft_strjoindel((char*)env->data, buffer);
        env->data_len += read_res;
        ft_bzero(buffer, 513);
    }
}

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
            init_data(env);
            get_input(env);
            ft_printf("%s", env->data);
            env->result = env->cmd(env->data, env->data_len);
            ft_printf("%s\n", env->result);
        }
        else if (c == 's') {}
        i++;
    }
    return 0;
}

void    get_options(t_env *env)
{
    int i;

    i = 0;
    while (i < env->option.opt_count && parse_option(env, i))
        i++;
}
