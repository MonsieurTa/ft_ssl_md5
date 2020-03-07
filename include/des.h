/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:23:21 by wta               #+#    #+#             */
/*   Updated: 2020/03/07 18:15:31 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# define BASE64_OPT			0x1
# define DECRYPT_OPT		0x2
# define ENCRYPT_OPT		0x4
# define KEY_OPT			0x8
# define PASSWORD_OPT		0x10
# define SALT_OPT			0x20
# define INIT_VECTOR_OPT	0x80

# define HASH_OUTPUT_SIZE	20
# define SALT_SIZE			8
# define ITERATION			2048

# define DK_SIZE			16

# define L					(DK_SIZE + HASH_OUTPUT_SIZE - 1) / HASH_OUTPUT_SIZE
# define R					DK_SIZE - (l - 1) * HASH_OUTPUT_SIZE

typedef struct	s_des
{
	char			*cmd_name;
	char			*input;
	char			*output;

	char			*key;
	uint8_t			salt[SALT_SIZE];
	uint32_t		saltsz;

	char			opt;
}				t_des;

void	str_xor_str_to_buffer(uint8_t *dst, uint8_t *a, uint8_t *b, uint32_t size);

int		set_des_cbc(t_des *des_env, char *name);
t_hash	prf(char *key, uint8_t salt[HASH_OUTPUT_SIZE], uint32_t saltsz);
int		pbkdf2(t_des *des_env);

#endif
