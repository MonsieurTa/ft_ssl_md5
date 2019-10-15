/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:54:27 by wta               #+#    #+#             */
/*   Updated: 2019/10/15 13:43:09 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdint.h>
# include <ft_ssl.h>

#define MD5_FN_F(b,c,d)			((b & c) | (~b & d))
#define MD5_FN_G(b,c,d)			((b & d) | (c & ~d))
#define MD5_FN_H(b,c,d)			(b ^ c ^ d)
#define MD5_FN_I(b,c,d)			(c ^ (b | ~d))
#define MD5_LEFT_ROTATE(x,c)	((x << c) | (x >> (32 - c)))

#define MD5_OUTPUT_SIZE 32
#define MD5_RESULT_SIZE 4

extern uint8_t	g_md5_g[];
extern uint8_t	g_left_shifts[];
extern uint32_t	g_constants[];

void			ft_ssl_get_result(t_env *env);
void  			md5_init(t_env *env);
void			md5(t_env *env, uint32_t *chunk);

#endif