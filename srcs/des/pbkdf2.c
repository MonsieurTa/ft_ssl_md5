/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:57:28 by wta               #+#    #+#             */
/*   Updated: 2020/02/29 17:31:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "ft_ssl.h"
#include "des.h"

static void	f(t_des *des_env, uint8_t u[], uint32_t i)
{
	uint8_t		buffer[HASH_OUTPUT_SIZE];
	t_hash		hash_env;
	uint32_t	c;

	ft_memcpy(buffer, des_env->salt, SALT_SIZE);
	ft_memcpy(buffer + SALT_SIZE, (uint8_t*)&i, 4);
	hash_env = prf(des_env->key, buffer);
	ft_memcpy(u, hash_env.output, HASH_OUTPUT_SIZE);
	c = 0;
	while (c < ITERATION)
	{
		hash_env = prf(des_env->key, u);
		str_xor_str_to_buffer(buffer, u, (uint8_t*)hash_env.output, HASH_OUTPUT_SIZE);
		ft_memcpy(u, buffer, HASH_OUTPUT_SIZE);
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
		f(des_env, u, i);
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
