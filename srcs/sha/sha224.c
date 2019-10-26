/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:02:08 by wta               #+#    #+#             */
/*   Updated: 2019/10/26 11:56:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	sha224_init(t_env *env)
{
	env->result[0] = 0xc1059ed8;
	env->result[1] = 0x367cd507;
	env->result[2] = 0x3070dd17;
	env->result[3] = 0xf70e5939;
	env->result[4] = 0xffc00b31;
	env->result[5] = 0x68581511;
	env->result[6] = 0x64f98fa7;
	env->result[7] = 0xbefa4fa4;
	env->output_size = FT_SSL_56_OUTPUT;
	env->big_endian = 1;
}
