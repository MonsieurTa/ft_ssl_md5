/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/11 15:23:51 by wta              ###   ########.fr       */
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
    if (ft_strequ(str, "md5"))
    {
        env->cmd = md5;
        return ;
    }
    if (ft_strequ(str, "sha256"))
    {
        return;
    }
    // Exit with error message
    exit(0);
}

int main(int ac, char **av)
{
    t_env   env;


    ft_bzero(&env, sizeof(t_env));
    if (ac > 1)
    {
        get_cmd(&env, av[1]);
        if (ac > 2)
        {
            env.option.opt_count = ac - 2;
            env.option.opt_list = &av[2];
            get_options(&env);
        }
    }
    else
    {
        exit(0);
    }
    return 0;
}