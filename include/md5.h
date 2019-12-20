/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:54:27 by wta               #+#    #+#             */
/*   Updated: 2019/12/20 16:57:33 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_FN	"md5_fn.c"

# include <stdint.h>
# include <ft_ssl.h>

extern uint8_t	g_md5_g[];
extern uint8_t	g_left_shifts[];
extern uint32_t	g_constants[];

void			ft_ssl_get_result(t_env *env);
void			md5_init(t_env *env);
int				set_md5(t_env *env, char *name);

#endif
