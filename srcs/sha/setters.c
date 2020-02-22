/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:55:31 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 14:35:11 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sha.h"
#include "ft_ssl.h"

int	set_sha1(t_hash *hash_env, char *name)
{
	if (!ft_strequ(name, "sha1"))
		return (0);
	hash_env->cmd = sha1;
	hash_env->init_cmd = sha1_init;
	return (1);
}

int	set_sha224(t_hash *hash_env, char *name)
{
	if (!ft_strequ(name, "sha224"))
		return (0);
	hash_env->cmd = sha256;
	hash_env->init_cmd = sha224_init;
	return (1);
}

int	set_sha256(t_hash *hash_env, char *name)
{
	if (!ft_strequ(name, "sha256"))
		return (0);
	hash_env->cmd = sha256;
	hash_env->init_cmd = sha256_init;
	return (1);
}
