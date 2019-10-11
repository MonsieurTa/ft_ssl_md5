/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:07:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/11 17:54:01 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"

uint32_t	g_constants[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

uint32_t	g_left_shifts[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

void init_msg(t_md5 *env_md5, uint8_t *data, uint64_t data_len)
{
	uint8_t		*msg;
	uint64_t	msg_len;
	uint64_t	bit_len;
	uint64_t	*len_anchor;

	bit_len = data_len * 8 + 1;
	msg_len = align_up(bit_len + 64, 512) / 8;
	if ((msg = (uint8_t*)malloc(msg_len * sizeof(uint8_t))) == NULL)
		exit(0);
	ft_bzero(msg, msg_len);
	msg = ft_memcpy(msg, data, data_len);
	msg[data_len] |= 1 << 7;
	len_anchor = (uint64_t*)&msg[msg_len-8];
	*len_anchor = data_len * 8;
	env_md5->msg = msg;
	env_md5->msg_len = msg_len;
}

void	process_digest(t_md5_digest *md5_digest, uint32_t g, uint32_t (*bitwise_fn)(uint32_t, uint32_t, uint32_t))
{
	md5_digest->f = bitwise_fn(md5_digest->b, md5_digest->c, md5_digest->d);
	md5_digest->g = g;
}

void	md5_digest(t_md5 *env_md5, uint32_t *chunk)
{
	t_md5_digest	md5_digest;
	int				i;

	i = 0;
	ft_bzero(&md5_digest, sizeof(t_md5_digest));
	init_md5_hash(env_md5, &md5_digest);
	while (i < 64)
	{
		if (i < 16)
			process_digest(&md5_digest, i, bitwise_fn_f);
		else if (i >= 16 && i < 32)
			process_digest(&md5_digest, (5 * i + 1) % 16, bitwise_fn_g);
		else if (i >= 32 && i < 48)
			process_digest(&md5_digest, (3 * i + 5) % 16, bitwise_fn_h);
		else if (i >= 48 && i < 64)
			process_digest(&md5_digest, (7 * i) % 16, bitwise_fn_i);
		assign_round_digest(&md5_digest, i, chunk);
		i++;
	}
	assign_digest(env_md5, &md5_digest);
}

char		*md5(uint8_t *data, uint64_t data_len)
{
	t_md5	env_md5;
	size_t	i;

	i = 0;
	ft_bzero(&env_md5, sizeof(t_md5));
	init_msg(&env_md5, data, data_len);
	env_md5.a0 = 0x67452301;
	env_md5.b0 = 0xefcdab89;
	env_md5.c0 = 0x98badcfe;
	env_md5.d0 = 0x10325476;
	while (i < env_md5.msg_len)
	{
		md5_digest(&env_md5, (uint32_t*)&env_md5.msg[i]);
		i += 64;
	}
	md5_join_result(&env_md5);
	md5_get_result(&env_md5);
	return ft_strdup(env_md5.result);
}
