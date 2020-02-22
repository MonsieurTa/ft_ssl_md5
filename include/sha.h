/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:07:18 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 14:35:27 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
# define SHA_H

# define SHA_FN	"sha_fn.c"

# include <stdint.h>
# include "ft_ssl.h"

void	assign_data_to_words(uint32_t words[64], uint32_t *chunk);

void	sha256(t_hash *hash_env, uint32_t *chunk);
void	sha256_init(t_hash *hash_env);

void	sha224_init(t_hash *hash_env);

void	sha1(t_hash *hash_env, uint32_t *chunk);
void	sha1_init(t_hash *hash_env);

int		set_sha1(t_hash *hash_env, char *name);
int		set_sha224(t_hash *hash_env, char *name);
int		set_sha256(t_hash *hash_env, char *name);

#endif
