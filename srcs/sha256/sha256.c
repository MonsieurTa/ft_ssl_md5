/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:30:13 by wta               #+#    #+#             */
/*   Updated: 2019/10/17 18:32:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "sha256.h"

static uint32_t g_sha256_k[] = {
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void	sha256_init(t_env *env)
{
	env->result[0] = 0x6a09e667;
	env->result[1] = 0xbb67ae85;
	env->result[2] = 0x3c6ef372;
	env->result[3] = 0xa54ff53a;
	env->result[4] = 0x510e527f;
	env->result[5] = 0x9b05688c;
	env->result[6] = 0x1f83d9ab;
	env->result[7] = 0x5be0cd19;
	env->output_size = SHA256_OUTPUT_SIZE;
}

static void	extend_words(uint32_t words[64])
{
	int			i;
	int			j;
	
	i = 16;
	while (i < CHUNK_SIZE)
	{
		j = i - 15;
    	words[i] = SSIG1(words[i - 2]) + words[i - 7] + SSIG0(j) + words[i - 16];
		i++;
	}
}

static void	assign_data_to_words(uint32_t words[64], uint32_t *chunk)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		words[i] = byte_swap32(chunk[i]);
		i++;
	}
}
void	sha256(t_env *env, uint32_t *chunk)
{
	uint32_t	words[64];
	uint32_t	digest[8];
	uint32_t	tmp1;
	uint32_t	tmp2;
	int			i;

	i = 0;
	ft_memcpy(digest, env->result, sizeof(uint32_t) * 8);
	assign_data_to_words(words, chunk);
	extend_words(words);
	while (i < CHUNK_SIZE)
	{
		tmp1 = digest[7] + BSIG1(digest[4]) + CH(digest[4], digest[5], digest[6]) + g_sha256_k[i] + words[i];
        tmp2 = BSIG0(digest[0]) + MAJ(digest[0], digest[1], digest[2]);
        digest[7] = digest[6];
        digest[6] = digest[5];
        digest[5] = digest[4];
        digest[4] = digest[3] + tmp1;
        digest[3] = digest[2];
        digest[2] = digest[1];
        digest[1] = digest[0];
        digest[0] = tmp1 + tmp2;
		i++;
	}
	env->result[0] += digest[0];
	env->result[1] += digest[1];
	env->result[2] += digest[2];
	env->result[3] += digest[3];
	env->result[4] += digest[4];
	env->result[5] += digest[5];
	env->result[6] += digest[6];
	env->result[7] += digest[7];
}
