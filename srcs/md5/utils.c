/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:26:55 by wta               #+#    #+#             */
/*   Updated: 2019/10/11 12:36:29 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void	init_md5_hash(t_md5 *md5, t_md5_digest *md5_hash)
{
	md5_hash->a = md5->a0;
	md5_hash->b = md5->b0;
	md5_hash->c = md5->c0;
	md5_hash->d = md5->d0;
}

void	md5_join_result(t_md5 *env_md5)
{
	env_md5->digest[0] = env_md5->a0;
	env_md5->digest[1] = env_md5->b0;
	env_md5->digest[2] = env_md5->c0;
	env_md5->digest[3] = env_md5->d0;
}

void	md5_get_result(t_md5 *env_md5)
{
	uint8_t	*ptr;
	int		i;

	i = 0;
	ptr = (uint8_t*)env_md5->digest;
	while (i < 31)
	{
		byte_to_hexa(&env_md5->result[i], ptr[i / 2]);
		i += 2;
	}
}

void	assign_round_digest(t_md5_digest *md5_digest, int i, uint32_t *chunk)
{
	md5_digest->f = md5_digest->f + md5_digest->a + g_constants[i] + chunk[md5_digest->g];
	md5_digest->a = md5_digest->d;
	md5_digest->d = md5_digest->c;
	md5_digest->c = md5_digest->b;
	md5_digest->b = md5_digest->b + left_rotate(md5_digest->f, g_left_shifts[i]);	
}

void assign_digest(t_md5 *env_md5, t_md5_digest *md5_digest)
{
	env_md5->a0 += md5_digest->a;
	env_md5->b0 += md5_digest->b;
	env_md5->c0 += md5_digest->c;
	env_md5->d0 += md5_digest->d;	
}