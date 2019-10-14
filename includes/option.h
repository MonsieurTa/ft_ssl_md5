/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:16:36 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 16:40:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

typedef struct s_env t_env;

typedef enum        e_error_type
{
    ERRNOERROR
}                   t_error_type;           

typedef struct      s_option_error
{
    t_error_type  type;
}                   t_option_error;

typedef struct      s_option
{
    int     opt_count;
    char    **opt_list;
    char    reverse : 1;
    char    quiet   : 1;

}                   t_option;

int    manage_options(t_env *env);

#endif
