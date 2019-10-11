/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:13:52 by wta               #+#    #+#             */
/*   Updated: 2019/10/09 13:38:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "option.h"

char    g_options[] = "pqrs";

#include <stdio.h>

// illegal option: exit with error msg
// int     parse_option(t_option *option, char *str)
// {
//     int i;

//     i = 0;
//     if (str[i++] == '-')
//     {
//         while (str[i])
//         {
//             if (ft_strchr(g_options, (int)str[i]))
//             else
//                 exit(0);
//             i++;
//         }
//         return 1;
//     }
//     return 0;
// }

void    get_options(t_option *option, int options_len, char **option_list)
{
    int i;
    int is_option;
    (void)option_list;
    (void)option;
    i = 0;
    is_option = 1;
    while (i < options_len && is_option)
    {
        // is_option = parse_option(option, option_list[i]);
        i++;
    }
}

void    option_manager(t_option *option, int ac, char **av)
{
    if (ac > 1)
    {
        if (ac > 2)
        {
            get_options(option, ac - 2, av + 2);
        }
    }
}
