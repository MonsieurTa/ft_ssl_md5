/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:16:36 by wta               #+#    #+#             */
/*   Updated: 2019/10/15 16:47:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

# define OPT_QUIET      0x1
# define OPT_REVERSE    0x2
# define OPT_PRINT      0x4
# define OPT_STRING     0x8

typedef struct s_env t_env;

typedef struct      s_option
{
    int     opt_count;
    char    **opt_list;
    char    opts;
    char    curr_opt;
}                   t_option;

int    manage_options(t_env *env);

#endif
