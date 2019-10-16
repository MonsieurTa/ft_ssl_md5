/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:09:03 by wta               #+#    #+#             */
/*   Updated: 2019/10/16 12:36:18 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "libft.h"

#include "ft_printf.h"

int		track_input(t_env *env, uint8_t *input_buffer)
{
	if (!env->input)
	{
		if (!(env->input = ft_strdup((char*)input_buffer)))
			return throw_error(env, ERR_PANIC);
	}
	else if (env->input)
	{
		if (!(env->input = ft_strjoindel(env->input, (char*)input_buffer)))
			return throw_error(env, ERR_PANIC);
	}
	return 1;
}