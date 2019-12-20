/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_fn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 17:03:39 by wta               #+#    #+#             */
/*   Updated: 2019/12/20 17:25:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

static inline uint32_t	lr(uint32_t x, uint32_t c)
{
	return (((x) << c) | ((x) >> (sizeof(x) * 8 - c)));
}

static inline uint32_t	rr(uint32_t x, uint32_t c)
{
	return (((x) >> c) | ((x) << (sizeof(x) * 8 - c)));
}

static inline uint32_t	ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

static inline uint32_t	maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

static inline uint32_t	par(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}
