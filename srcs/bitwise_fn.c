/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:51:46 by wta               #+#    #+#             */
/*   Updated: 2019/10/09 16:55:23 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t	bitwise_fn_f(uint32_t b, uint32_t c, uint32_t d)
{
	return (b & c) | (~b & d);
}
uint32_t	bitwise_fn_g(uint32_t b, uint32_t c, uint32_t d)
{
	return (b & d) | (c & ~d);
}
uint32_t	bitwise_fn_h(uint32_t b, uint32_t c, uint32_t d)
{
	return b ^ c ^ d;
}
uint32_t	bitwise_fn_i(uint32_t b, uint32_t c, uint32_t d)
{
	return c ^ (b | ~d);
}
