/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:26:55 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 19:10:11 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void	md5_init(t_digest_tool *tool, t_md5_digest *md5_digest)
{
	md5_digest->a = tool->a0;
	md5_digest->b = tool->b0;
	md5_digest->c = tool->c0;
	md5_digest->d = tool->d0;
}

void	md5_join_result(t_digest_tool *tool, t_env *env)
{
	env->digest_result[0] = tool->a0;
	env->digest_result[1] = tool->b0;
	env->digest_result[2] = tool->c0;
	env->digest_result[3] = tool->d0;
}

void	md5_get_result(t_env *env)
{
	uint8_t	*ptr;
	int		i;

	i = 0;
	ptr = (uint8_t*)env->digest_result;
	while (i < 31)
	{
		byte_to_hexa(&env->result[i], ptr[i / 2]);
		i += 2;
	}
}

void	assign_round_digest(t_md5_digest *md5_digest, int i, uint32_t *chunk)
{
	md5_digest->f = md5_digest->f + md5_digest->a + g_constants[i] + chunk[md5_digest->g];
	md5_digest->a = md5_digest->d;
	md5_digest->d = md5_digest->c;
	md5_digest->c = md5_digest->b;
	md5_digest->b = md5_digest->b + MD5_LEFT_ROTATE(md5_digest->f, g_left_shifts[i]);	
}

void 	md5_sum_digest(t_digest_tool *tool, t_md5_digest *md5_digest)
{
	tool->a0 += md5_digest->a;
	tool->b0 += md5_digest->b;
	tool->c0 += md5_digest->c;
	tool->d0 += md5_digest->d;	
}