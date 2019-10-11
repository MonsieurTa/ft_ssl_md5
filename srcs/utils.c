/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:12:20 by wta               #+#    #+#             */
/*   Updated: 2019/10/09 16:41:13 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl.h"

void	swap_byte(void *ptr, uint32_t size)
{
	uint32_t	low;
	uint8_t		tmp;
	uint8_t		*cptr;

	cptr = ptr;
	low = 0;
	while (low < size)
	{
		size--;
		tmp = cptr[size];
		cptr[size] = cptr[low];
		cptr[low] = tmp;
		low++;
	}
}

uint64_t	align_up(int n, uint64_t mod)
{
	uint64_t	res;

	res = n % mod;
	return res == 0 ? (
		n
	) : (n - res) + mod;
}

uint32_t	left_rotate(uint32_t x, uint32_t c)
{
	return (x << c) | (x >> (32 - c));
}
