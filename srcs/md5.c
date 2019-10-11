/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:07:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/10 19:14:16 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"

#include <stdio.h>

uint32_t	g_contants[] = {
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

	bit_len = data_len * 8 + 1; // 1 bit a end of message
	// need to get to bit_len = 448 % 512
	msg_len = align_up(bit_len + 64, 512) / 8;
	msg = (uint8_t*)malloc(msg_len * sizeof(uint8_t));
	ft_bzero(msg, msg_len);
	msg = ft_memcpy(msg, data, data_len);
	msg[data_len] |= 1 << 7; // append 1 to end of msg
	len_anchor = (uint64_t*)&msg[msg_len-8];
	*len_anchor = data_len * 8; // setting the original data length on 64 bits
	env_md5->msg = msg;
	env_md5->msg_len = msg_len;
}

void	init_md5_hash(t_md5 *md5, t_md5_hash *md5_hash)
{
	md5_hash->a = md5->a0;
	md5_hash->b = md5->b0;
	md5_hash->c = md5->c0;
	md5_hash->d = md5->d0;
}

void	hash_data(t_md5 *env_md5, uint32_t *chunk)
{
	t_md5_hash	md5_hash;
	int			i;

	i = 0;
	ft_bzero(&md5_hash, sizeof(t_md5_hash));

	init_md5_hash(env_md5, &md5_hash);
	while (i < 64)
	{
		if (i < 16)
		{
			md5_hash.f = bitwise_fn_f(md5_hash.b, md5_hash.c, md5_hash.d);
			md5_hash.g = i;
		}
		else if (i >= 16 && i < 32)
		{
			md5_hash.f = bitwise_fn_g(md5_hash.b, md5_hash.c, md5_hash.d);
			md5_hash.g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i < 48)
		{
			md5_hash.f = bitwise_fn_h(md5_hash.b, md5_hash.c, md5_hash.d);
			md5_hash.g = (3 * i + 5) % 16;
		}
		else if (i >= 48 && i < 64)
		{
			md5_hash.f = bitwise_fn_i(md5_hash.b, md5_hash.c, md5_hash.d);
			md5_hash.g = (7 * i) % 16;
		}
		md5_hash.f = md5_hash.f + md5_hash.a + g_contants[i] + chunk[md5_hash.g];
		md5_hash.a = md5_hash.d;
		md5_hash.d = md5_hash.c;
		md5_hash.c = md5_hash.b;
		md5_hash.b = md5_hash.b + left_rotate(md5_hash.f, g_left_shifts[i]);
		i++;
	}
	env_md5->a0 += md5_hash.a;
	env_md5->b0 += md5_hash.b;
	env_md5->c0 += md5_hash.c;
	env_md5->d0 += md5_hash.d;
}

void	digest_md5(t_md5 *env_md5)
{
	env_md5->digest[0] = env_md5->a0;
	env_md5->digest[1] = env_md5->b0;
	env_md5->digest[2] = env_md5->c0;
	env_md5->digest[3] = env_md5->d0;
}

void	byte_to_hexa(char *dst, uint8_t byte)
{
	dst[0] = "0123456789abcdef"[byte >> 4];
	dst[1] = "0123456789abcdef"[byte & 0xf];
}

void	digest_to_hexa(t_md5 *env_md5)
{
	char	result[32];
	uint8_t	*ptr;

	ptr = (uint8_t*)env_md5->digest;
	for (int i = 0; i < 31; i += 2)
	{
		byte_to_hexa(&result[i], ptr[i / 2]);
	}
	write(1, result, 32);
	write(1, "\n", 1);
}

int		md5(t_env *env)
{
	t_md5	env_md5;

	ft_bzero(&env_md5, sizeof(t_md5));
	env_md5.a0 = 0x67452301;
	env_md5.b0 = 0xefcdab89;
	env_md5.c0 = 0x98badcfe;
	env_md5.d0 = 0x10325476;
	// Test
	env->data = (uint8_t*)"Hello";
	env->data_len = (uint64_t)ft_strlen((char*)env->data);

	init_msg(&env_md5, env->data, env->data_len);

	for (size_t i = 0; i < env_md5.msg_len; i += 64)
	{
		hash_data(&env_md5, (uint32_t*)&env_md5.msg[i]);
	}
	printf("msg len: %llu\n", env_md5.msg_len);
	digest_md5(&env_md5);
	digest_to_hexa(&env_md5);
	return 0;
}
