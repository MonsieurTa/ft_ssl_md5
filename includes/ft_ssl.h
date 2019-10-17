/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:31:34 by wta               #+#    #+#             */
/*   Updated: 2019/10/17 18:01:42 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include "option.h"

# define MIN(a,b)			(a < b ? a : b)

# define READ_BUFFER_LEN	4096
# define MAX_CMD_SIZE		64
# define CHUNK_SIZE			64
# define OUTPUT_SIZE		256

# define ERRNOERROR			0x1
# define ERR_BAD_CMD		0x2
# define ERR_USAGE			0x4
# define ERR_ILLEGAL_OPT	0x8
# define ERR_MISSING		0x10
# define ERR_INVALID_FILE	0x20
# define ERR_PANIC			0x40
# define ERR_OPT_REQ_ARG	0x80

typedef struct	s_digest_buffer
{
	uint8_t		r_buffer[READ_BUFFER_LEN + 1];
	uint8_t		buffer[CHUNK_SIZE + 1];
	uint32_t	len;
}				t_digest_buffer;

typedef struct	s_env
{
	char			cmd_name[MAX_CMD_SIZE + 1];
	t_option		option;
	char			*input_src;
	char			*input;
	uint64_t		data_len;
	t_digest_buffer	d_buffer;
	void			(*cmd)(t_env*, uint32_t*);
	void			(*init_cmd)(t_env*);
	uint32_t		result[8];
	char			output[OUTPUT_SIZE + 1];
	uint8_t			output_size;
}				t_env;

void		ft_ssl_read(t_env *env, int fd);
void		ft_ssl_string(t_env *env, char *str);
void		digest_files(t_env *env, char **filepaths, int index_max);
int			digest_string(t_env *env, char *residual_opt, int index);
void		end_digest(t_env *env);
int			track_input(t_env *env, uint8_t *input_buffer);
void		process_round(t_env *env, size_t start, size_t end, uint8_t *data);
void		fill_buffer(t_digest_buffer *d_buffer, uint8_t *r_buffer, size_t size);

void		format_output(t_env *env);

void    	print_bit(char c, int len);
uint64_t	align_up(int n, uint64_t mod);
uint32_t	byte_swap32(uint32_t x);
uint64_t	byte_swap64(uint64_t x);
void		byte_to_hexa(char *dst, uint8_t byte);
void		print_to_upper(char *str);

int			throw_error(t_env *env, int err_code);


#endif