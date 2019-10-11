/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2019/10/09 14:31:29 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "option.h"

char    *g_cmd[] = {
    "md5",
};

void    get_cmd(t_env *env, char *str)
{
    int i ;
    (void)env;
    i = 0;
    while (g_cmd[i])
    {
        if (ft_strequ(str, g_cmd[i]))
        {
            // assign digest_fn (md5, sha-256...)
            return ;
        }
        i++;
    }
    exit(0);
}

void    print_bit(char c, int len)
{
    char    result[len + 1];

    result[len] = '\0';
    for (int i = 0; i < len; i++) {
        result[len - i - 1] = c & 1 ? '1' : '0';
        c >>= 1;
    }
    printf("%s ", result);
}

int main(int ac, char **av)
{
    t_env   env;
    (void)ac;
    (void)av;
    ft_bzero(&env, sizeof(t_env));
    // get_cmd(&env, av[1]);
    // option_manager(&env.option, ac, av);
    md5(&env);
    
    return 0;
}