/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 17:24:44 by wta               #+#    #+#             */
/*   Updated: 2019/12/20 17:24:52 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

static inline uint32_t	md5_fn_f(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (~b & d));
}

static inline uint32_t	md5_fn_g(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & d) | (c & ~d));
}

static inline uint32_t	md5_fn_h(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

static inline uint32_t	md5_fn_i(uint32_t b, uint32_t c, uint32_t d)
{
	return (c ^ (b | ~d));
}
