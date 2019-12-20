/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:07:18 by wta               #+#    #+#             */
/*   Updated: 2019/12/20 17:01:08 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
# define SHA_H

# define SHA_FN	"sha_fn.c"

# include <stdint.h>
# include "ft_ssl.h"

void	assign_data_to_words(uint32_t words[64], uint32_t *chunk);

void	sha256(t_env *env, uint32_t *chunk);
void	sha256_init(t_env *env);

void	sha224_init(t_env *env);

void	sha1(t_env *env, uint32_t *chunk);
void	sha1_init(t_env *env);

int		set_sha1(t_env *env, char *name);
int		set_sha224(t_env *env, char *name);
int		set_sha256(t_env *env, char *name);

#endif
