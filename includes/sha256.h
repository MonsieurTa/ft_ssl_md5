/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:07:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/17 18:31:56 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# define ROTR(x,c)			((x >> c) | (x << (32 - c)))
# define CH(x,y,z)			((x & y) ^ (~x & z))
# define MAJ(x,y,z) 		((x & y) ^ (x & z) ^ (y & z))
# define BSIG0(x)			((ROTR(x,2)) ^ ROTR(x,13) ^ ROTR(x,22))
# define BSIG1(x)			((ROTR(x,6)) ^ (ROTR(x,11)) ^ (ROTR(x,25)))
# define SSIG0(x)			((ROTR(x,7)) ^ (ROTR(x,18)) ^ ((x) >> 3))
# define SSIG1(x)			((ROTR(x,17)) ^ (ROTR(x,19)) ^ ((x) >> 10))
# define SHA256_OUTPUT_SIZE	64

# include <stdint.h>
# include "ft_ssl.h"

void	sha256(t_env *env, uint32_t *chunk);
void	sha256_init(t_env *env);

#endif