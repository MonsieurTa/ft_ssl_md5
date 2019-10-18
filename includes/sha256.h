/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:07:18 by wta               #+#    #+#             */
/*   Updated: 2019/10/18 11:55:57 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# define RROT(n, s)			(((n) >> s) | ((n) << (sizeof(n) * 8 - s)))
# define CH(x,y,z)			((x & y) ^ (~x & z))
# define MAJ(x,y,z) 		((x & y) ^ (x & z) ^ (y & z))
# define BSIG0(x)			((RROT(x,2)) ^ (RROT(x,13)) ^ (RROT(x,22)))
# define BSIG1(x)			((RROT(x,6)) ^ (RROT(x,11)) ^ (RROT(x,25)))
# define SSIG0(x)			((RROT(x,7)) ^ (RROT(x,18)) ^ ((x) >> 3))
# define SSIG1(x)			((RROT(x,17)) ^ (RROT(x,19)) ^ ((x) >> 10))

# define SHA256_OUTPUT_SIZE	64

# include <stdint.h>
# include "ft_ssl.h"

void	sha256(t_env *env, uint32_t *chunk);
void	sha256_init(t_env *env);

#endif