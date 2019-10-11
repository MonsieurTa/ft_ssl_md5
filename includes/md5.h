/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:54:27 by wta               #+#    #+#             */
/*   Updated: 2019/10/11 12:34:42 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdint.h>
typedef struct	s_md5
{
	uint8_t		*msg;
	uint64_t	msg_len;
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
	uint32_t	digest[4];
	char		result[32];
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

void			init_md5_hash(t_md5 *md5, t_md5_digest *md5_hash);
void			md5_join_result(t_md5 *env_md5);
void			md5_get_result(t_md5 *env_md5);
void			assign_round_digest(t_md5_digest *md5_digest, int i, uint32_t *chunk);
void			assign_digest(t_md5 *env_md5, t_md5_digest *md5_digest);

int				md5(t_env *env);
uint32_t		bitwise_fn_f(uint32_t b, uint32_t c, uint32_t d);
uint32_t		bitwise_fn_g(uint32_t b, uint32_t c, uint32_t d);
uint32_t		bitwise_fn_h(uint32_t b, uint32_t c, uint32_t d);
uint32_t		bitwise_fn_i(uint32_t b, uint32_t c, uint32_t d);

#endif