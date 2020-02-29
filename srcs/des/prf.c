/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:23:13 by wta               #+#    #+#             */
/*   Updated: 2020/02/29 14:51:53 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "sha.h"
#include "des.h"

static char	g_outer_pad[CHUNK_SIZE] = {
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
	0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
};

static char	g_inner_pad[CHUNK_SIZE] = {
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
};

static void	pad(char *src, size_t i)
{
	while (i < CHUNK_SIZE)
	{
		src[i] = '0';
		i++;
	}
}

static void	str_xor_str_to_buffer(char *dst, char *a, char *b, uint32_t size)
{
	uint32_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = a[i] ^ b[i];
		i++;
	}
}

static void	process_prf(t_hash *hash_env, char key[], char salt[])
{
	char		out[CHUNK_SIZE + FT_SSL_40_OUTPUT + 1];
	char		buffer[CHUNK_SIZE + SALT_SIZE + 1];

	ft_bzero(buffer, sizeof(buffer));
	str_xor_str_to_buffer(buffer, key, g_inner_pad, CHUNK_SIZE);
	ft_memcpy(buffer + CHUNK_SIZE, salt, SALT_SIZE);
	hash_env->init_cmd(hash_env);
	ft_ssl_string(hash_env, buffer);
	ft_bzero(buffer, sizeof(buffer));
	str_xor_str_to_buffer(buffer, key, g_outer_pad, CHUNK_SIZE);
	ft_bzero(out, sizeof(out));
	ft_memcpy(out, buffer, CHUNK_SIZE);
	ft_memcpy(out + CHUNK_SIZE, hash_env->output, FT_SSL_40_OUTPUT);
	hash_env->init_cmd(hash_env);
	ft_ssl_string(hash_env, out);
}

/*
**	pw has a variable length, salt is 16 + 4 bytes long
*/

t_hash		prf(char *key, char salt[])
{
	char		prepared_key[CHUNK_SIZE + 1];
	t_hash		hash_env;
	size_t		len;

	ft_bzero(&hash_env, sizeof(t_hash));
	set_sha1(&hash_env, "sha1");
	len = ft_strlen(key);
	if (len > CHUNK_SIZE)
		ft_ssl_string(&hash_env, key);
	ft_bzero(prepared_key, sizeof(prepared_key));
	ft_memcpy(prepared_key, len > CHUNK_SIZE ? hash_env.output : key,
							len > CHUNK_SIZE ? FT_SSL_40_OUTPUT : len);
	len = ft_strlen(prepared_key);
	if (len < CHUNK_SIZE)
		pad(prepared_key, len);
	process_prf(&hash_env, prepared_key, salt);
	return (hash_env);
}
