/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:31:34 by wta               #+#    #+#             */
/*   Updated: 2019/10/11 12:37:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdint.h>
#include "option.h"

typedef struct	s_env
{
	t_option	option;
	uint8_t		*data;
	uint64_t	data_len;
	uint64_t	data_bitlen;
	char		**filenames;
	void		(*digest_fn)(t_option *opt, char *data);
}				t_env;

void    	print_bit(char c, int len);
uint64_t	align_up(int n, uint64_t mod);
uint32_t	left_rotate(uint32_t x, uint32_t c);
void		byte_to_hexa(char *dst, uint8_t byte);


#endif