/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:54:27 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 19:02:31 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdint.h>
# include <ft_ssl.h>

#define MD5_FN_F(b,c,d) ((b & c) | (~b & d))
#define MD5_FN_G(b,c,d) ((b & d) | (c & ~d))
#define MD5_FN_H(b,c,d) (b ^ c ^ d)
#define MD5_FN_I(b,c,d) (c ^ (b | ~d))
#define MD5_LEFT_ROTATE(x,c) ((x << c) | (x >> (32 - c)))

typedef struct	s_md5
{
	uint8_t		*msg;
	uint64_t	msg_len;
}				t_md5;

typedef struct	s_md5_digest
{
	uint32_t	f;
	uint32_t	g;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_md5_digest;

extern uint32_t	g_left_shifts[];
extern uint32_t	g_constants[];

void			md5_init(t_digest_tool *tool, t_md5_digest *md5_hash);
void			md5_join_result(t_digest_tool *tool, t_env *env);
void			md5_get_result(t_env *env);
void			assign_round_digest(t_md5_digest *md5_digest, int i, uint32_t *chunk);
void			md5_sum_digest(t_digest_tool *tool, t_md5_digest *md5_digest);

void			md5(t_env *env, uint32_t *chunk);

#endif