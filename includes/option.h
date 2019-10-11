/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:16:36 by wta               #+#    #+#             */
/*   Updated: 2019/10/09 11:40:44 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

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


}                   t_option;

void    option_manager(t_option *option, int ac, char **av);

#endif
