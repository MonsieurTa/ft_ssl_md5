/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:55:31 by wta               #+#    #+#             */
/*   Updated: 2019/10/26 12:45:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sha.h"
#include "ft_ssl.h"

int	set_sha1(t_env *env, char *name)
{
	if (!ft_strequ(name, "sha1"))
		return (0);
	env->cmd = sha1;
	env->init_cmd = sha1_init;
	return (1);
}

int	set_sha224(t_env *env, char *name)
{
	if (!ft_strequ(name, "sha224"))
		return (0);
	env->cmd = sha256;
	env->init_cmd = sha224_init;
	return (1);
}

int	set_sha256(t_env *env, char *name)
{
	if (!ft_strequ(name, "sha256"))
		return (0);
	env->cmd = sha256;
	env->init_cmd = sha256_init;
	return (1);
}
