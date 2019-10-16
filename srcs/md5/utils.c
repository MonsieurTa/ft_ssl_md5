/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:26:55 by wta               #+#    #+#             */
/*   Updated: 2019/10/16 15:16:52 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_ssl.h"
#include "md5.h"

void	ft_ssl_get_result(t_env *env)
{
	uint8_t	*ptr;
	int		i;

	i = 0;
	ptr = (uint8_t*)env->result;
	while (i < env->output_size - 1)
	{
		byte_to_hexa(&env->output[i], ptr[i / 2]);
		i += 2;
	}
	format_output(env);
}

void    md5_init(t_env *env)
{
    env->result[0] = 0x67452301;
	env->result[1] = 0xefcdab89;
	env->result[2] = 0x98badcfe;
	env->result[3] = 0x10325476;
	env->output_size = MD5_OUTPUT_SIZE;
}
