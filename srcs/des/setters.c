/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:20:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/28 09:54:49 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"

int	set_des_cbc(t_des *des_env, char *name)
{
	if (!ft_strequ("des-cbc", name) && !ft_strequ("des", name))
		return (0);
	(void)des_env;

	return (1);
}
