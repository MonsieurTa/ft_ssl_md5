/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:23:13 by wta               #+#    #+#             */
/*   Updated: 2020/03/07 18:05:27 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "sha.h"
#include "des.h"

static uint8_t	g_outer_pad[] = {
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
};

static uint8_t	g_inner_pad[] = {
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
};

void		str_xor_str_to_buffer(uint8_t *dst, uint8_t *a, uint8_t *b, uint32_t size)
{
	uint32_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = a[i] ^ b[i];
		i++;
	}
}

static void		process_prf(t_hash *hash_env, char key[], uint8_t salt[], uint32_t saltsz)
{
	uint8_t		out[CHUNK_SIZE + HASH_OUTPUT_SIZE + 1];
	uint8_t		buffer[CHUNK_SIZE + HASH_OUTPUT_SIZE + 1];

	ft_bzero(buffer, sizeof(buffer));
	str_xor_str_to_buffer(buffer, (uint8_t*)key, g_inner_pad, CHUNK_SIZE);
	ft_memcpy(buffer + CHUNK_SIZE, salt, saltsz);
	hash_env->init_cmd(hash_env);
	ft_ssl_string(hash_env, (char*)buffer, CHUNK_SIZE + saltsz);
	ft_bzero(buffer, sizeof(buffer));
	str_xor_str_to_buffer(buffer, (uint8_t*)key, g_outer_pad, CHUNK_SIZE);
	ft_bzero(out, sizeof(out));
	ft_memcpy(out, buffer, CHUNK_SIZE);
	ft_memcpy(out + CHUNK_SIZE, hash_env->result, HASH_OUTPUT_SIZE);
	hash_env->init_cmd(hash_env);
	ft_ssl_string(hash_env, (char*)out, CHUNK_SIZE + HASH_OUTPUT_SIZE);
}

/*
**	pw has a variable length, salt is 16 + 4 bytes long
*/

t_hash			prf(char *key, uint8_t salt[], uint32_t saltsz)
{
	char		prepared_key[CHUNK_SIZE + 1];
	t_hash		hash_env;
	size_t		len;

	ft_bzero(&hash_env, sizeof(t_hash));
	set_sha1(&hash_env, "sha1");
	len = ft_strlen(key);
	if (len > CHUNK_SIZE)
		ft_ssl_string(&hash_env, key, len);
	ft_bzero(prepared_key, sizeof(prepared_key));
	ft_memcpy(prepared_key, len > CHUNK_SIZE ? (void*)hash_env.result : key,
							len > CHUNK_SIZE ? HASH_OUTPUT_SIZE : len);
	process_prf(&hash_env, prepared_key, salt, saltsz);
	return (hash_env);
}
