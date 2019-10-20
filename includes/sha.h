/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:07:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/21 11:50:29 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
# define SHA_H

# define BSIG0(x)			((RR(x,2)) ^ (RR(x,13)) ^ (RR(x,22)))
# define BSIG1(x)			((RR(x,6)) ^ (RR(x,11)) ^ (RR(x,25)))
# define SSIG0(x)			((RR(x,7)) ^ (RR(x,18)) ^ ((x) >> 3))
# define SSIG1(x)			((RR(x,17)) ^ (RR(x,19)) ^ ((x) >> 10))

# include <stdint.h>
# include "ft_ssl.h"

void	assign_data_to_words(uint32_t words[64], uint32_t *chunk);

void	sha256(t_env *env, uint32_t *chunk);
void	sha256_init(t_env *env);

void	sha224_init(t_env *env);

void	sha1(t_env *env, uint32_t *chunk);
void	sha1_init(t_env *env);

#endif
