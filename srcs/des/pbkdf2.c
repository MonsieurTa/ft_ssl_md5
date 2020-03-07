/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:57:28 by wta               #+#    #+#             */
/*   Updated: 2020/03/07 18:13:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "sha.h"
#include "des.h"

#include <stdlib.h>
#include "ft_printf.h"

static void	f(t_des *des_env, uint8_t u[], uint32_t i)
{
	uint8_t		buffer[HASH_OUTPUT_SIZE];
	t_hash		hash_env;
	uint32_t	c;

	ft_memcpy(buffer, des_env->salt, des_env->saltsz);
	i = byte_swap32(i);
	ft_memcpy(buffer + des_env->saltsz, (uint8_t*)&i, sizeof(i));
	hash_env = prf(des_env->key, buffer, des_env->saltsz + sizeof(i));
	ft_memcpy(u, hash_env.result, HASH_OUTPUT_SIZE);
	c = 1;
	while (c < ITERATION)
	{
		hash_env = prf(des_env->key, (uint8_t*)hash_env.result, HASH_OUTPUT_SIZE);
		str_xor_str_to_buffer(u, u, (uint8_t*)hash_env.result, HASH_OUTPUT_SIZE);
		c++;
	}
}

/*
**	l = ceil(dkLen / hash_output_size);
**	ceil function: q = (x + y - 1) / y;
*/

int		pbkdf2(t_des *des_env)
{
	uint8_t		out[DK_SIZE * 2 + 1];
	uint8_t		t[L * HASH_OUTPUT_SIZE];
	uint8_t		u[HASH_OUTPUT_SIZE];
	uint32_t	i;

	i = 0;
	while (i < L)
	{
		f(des_env, u, i + 1);
		ft_memcpy(t + (i * HASH_OUTPUT_SIZE), u, HASH_OUTPUT_SIZE);
		i++;
	}
	ft_bzero(out, sizeof(out));
	i = 0;
	while (i < DK_SIZE)
	{
		byte_to_hexa((char*)(out + (i * 2)), t[i]);
		i++;
	}
	ft_printf("%s\n", out);
	return (1);
}
