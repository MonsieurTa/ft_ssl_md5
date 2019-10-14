/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:31:34 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 18:43:59 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdint.h>
#include "option.h"

#define READ_BUFFER_LEN 4096

typedef struct	s_digest_tool
{
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
}				t_digest_tool;

typedef struct	s_digest_buffer
{
	uint8_t		buffer[64 + 1];
	uint32_t	len;
}				t_digest_buffer;

typedef struct	s_env
{
	t_option		option;
	uint64_t		data_len;
	t_digest_buffer	d_buffer;
	t_digest_tool	tool;
	void			(*cmd)(t_env*, uint32_t*);
	void			(*init_cmd)(t_digest_tool*);
	uint32_t		digest_result[4];
	char			result[33];
}				t_env;

void		ft_ssl_read(t_env *env, int fd);
void		digest_files(t_env *env, char **filepaths, int index_max);

void    	print_bit(char c, int len);
uint64_t	align_up(int n, uint64_t mod);
void		byte_to_hexa(char *dst, uint8_t byte);


#endif