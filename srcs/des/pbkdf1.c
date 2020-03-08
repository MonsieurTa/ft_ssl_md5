/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:40:16 by wta               #+#    #+#             */
/*   Updated: 2020/03/08 19:54:54 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ssl.h"
#include "sha.h"
#include "des.h"
#include "ft_printf.h"

int		pbkdf1(t_des *des_env)
{
	uint8_t		out[DK_SIZE * 2 + 1];
	t_hash		hash_env;
	char		*str;
	uint32_t	keysz;
	uint32_t	i;

	ft_bzero(out, sizeof(out));
	ft_bzero(&hash_env, sizeof(t_hash));
	set_sha1(&hash_env, "sha1");
	keysz = ft_strlen(des_env->key);
	str = malloc(keysz + SALT_SIZE + 1);
	str[keysz + SALT_SIZE] = '\0';
	ft_memcpy(str, des_env->key, keysz);
	ft_memcpy(str + keysz, des_env->salt, SALT_SIZE);
	ft_ssl_string(&hash_env, str, keysz + SALT_SIZE);
	ft_memdel((void**)&str);
	i = 0;
	while (i < DK_SIZE)
	{
		byte_to_hexa((char*)(out) + (i * 2), *((uint8_t*)hash_env.result + i));
		i++;
	}
	ft_printf("%s\n", out);
	return (1);
}
