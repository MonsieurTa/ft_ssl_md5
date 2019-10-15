/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/15 14:48:12 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "option.h"

void    get_cmd(t_env *env, char *str)
{
    ft_memcpy(env->cmd_name, str, MIN(MAX_CMD_SIZE, ft_strlen(str)));
    if (ft_strequ(str, "md5"))
    {
        env->cmd = md5;
        env->init_cmd = md5_init;
        return ;
    }
    else if (ft_strequ(str, "sha256"))
    {
        return;
    }
    new_error(env, ERR_BAD_CMD);
}

int main(int ac, char **av)
{
    t_env   env;
    int     files_index;

    ft_bzero(&env, sizeof(t_env));
    if (ac > 1)
    {
        get_cmd(&env, av[1]);
        if (ac > 2)
        {
            env.option.opt_count = ac - 2;
            env.option.opt_list = &av[2];
            files_index = manage_options(&env);
            if (files_index != -1)
                digest_files(&env, &av[files_index], ac - 2);
        }
    }
    else
        new_error(&env, ERR_USAGE);
    return 0;
}