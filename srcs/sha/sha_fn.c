/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_fn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:59:42 by wta               #+#    #+#             */
/*   Updated: 2019/12/20 17:18:21 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl.h"
#include SSL_FN

static inline uint32_t	bsig0(uint32_t x)
{
	return ((rr(x, 2)) ^ (rr(x, 13)) ^ (rr(x, 22)));
}

static inline uint32_t	bsig1(uint32_t x)
{
	return ((rr(x, 6)) ^ (rr(x, 11)) ^ (rr(x, 25)));
}

static inline uint32_t	ssig0(uint32_t x)
{
	return ((rr(x, 7)) ^ (rr(x, 18)) ^ ((x) >> 3));
}

static inline uint32_t	ssig1(uint32_t x)
{
	return ((rr(x, 17)) ^ (rr(x, 19)) ^ ((x) >> 10));
}
