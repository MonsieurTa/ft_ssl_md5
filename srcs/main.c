/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 19:39:36 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "option.h"

void    init_md5_tool(t_digest_tool *tool)
{
    tool->a0 = 0x67452301;
	tool->b0 = 0xefcdab89;
	tool->c0 = 0x98badcfe;
	tool->d0 = 0x10325476;
}

void    get_cmd(t_env *env, char *str)
{
    if (ft_strequ(str, "md5"))
    {
        env->cmd = md5;
        env->init_cmd = init_md5_tool;
        return ;
    }
    else if (ft_strequ(str, "sha256"))
    {
        return;
    }
    // Exit with error message
    exit(0);
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
        exit(0);
    return 0;
}