/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:02:08 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 14:35:51 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	sha224_init(t_hash *hash_env)
{
	hash_env->result[0] = 0xc1059ed8;
	hash_env->result[1] = 0x367cd507;
	hash_env->result[2] = 0x3070dd17;
	hash_env->result[3] = 0xf70e5939;
	hash_env->result[4] = 0xffc00b31;
	hash_env->result[5] = 0x68581511;
	hash_env->result[6] = 0x64f98fa7;
	hash_env->result[7] = 0xbefa4fa4;
	hash_env->output_size = FT_SSL_56_OUTPUT;
	hash_env->big_endian = 1;
}
