/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:23:15 by wta               #+#    #+#             */
/*   Updated: 2019/10/20 16:51:54 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "sha.h"

static uint32_t	g_sha1_k[] = {
	0x5A827999,
	0x6ED9EBA1,
	0x8F1BBCDC,
	0xCA62C1D6,
};

static uint32_t	sha1_assign(int i, uint32_t digest[])
{
	if (i < 20)
		return (CH(digest[1], digest[2], digest[3]));
	else if (i < 40)
		return (PAR(digest[1], digest[2], digest[3]));
	else if (i < 60)
		return (MAJ(digest[1], digest[2], digest[3]));
	else
		return (PAR(digest[1], digest[2], digest[3]));
}

static void		extend_words(uint32_t w[])
{
	int	i;

	i = 15;
	while (++i < 80)
		w[i] = LR((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);
}

void			sha1_init(t_env *env)
{
	md5_init(env);
	env->result[4] = 0xC3D2E1F0;
	env->output_size = FT_SSL_40_OUTPUT;
	env->big_endian = 1;
}

void			sha1(t_env *env, uint32_t *chunk)
{
	uint32_t	w[80];
	uint32_t	digest[5];
	uint32_t	f;
	int			i;

	i = 15;
	ft_memcpy(digest, env->result, sizeof(uint32_t) * 5);
	assign_data_to_words(w, chunk);
	extend_words(w);
	i = -1;
	while (++i < 80)
	{
		f = sha1_assign(i, digest);
		f = LR(digest[0], 5) + f + digest[4] + g_sha1_k[i / 20] + w[i];
		digest[4] = digest[3];
		digest[3] = digest[2];
		digest[2] = LR(digest[1], 30);
		digest[1] = digest[0];
		digest[0] = f;
	}
	i = -1;
	while (++i < 5)
		env->result[i] += digest[i];
}
