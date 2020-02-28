/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:31:34 by wta               #+#    #+#             */
/*   Updated: 2020/02/28 09:48:31 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# define SSL_FN							"../utils/ssl_fn.c"

# define READ_BUFFER_LEN		4096
# define MAX_CMD_SIZE				64
# define CHUNK_SIZE					64
# define OUTPUT_SIZE				256

# define ERRNOERROR					0x1
# define ERR_BAD_CMD				0x2
# define ERR_USAGE					0x4
# define ERR_ILLEGAL_OPT		0x8
# define ERR_MISSING				0x10
# define ERR_INVALID_FILE		0x20
# define ERR_PANIC					0x40
# define ERR_OPT_REQ_ARG		0x80

# define FT_SSL_64_OUTPUT		64
# define FT_SSL_56_OUTPUT		56
# define FT_SSL_40_OUTPUT		40
# define FT_SSL_32_OUTPUT		32

# include <stdint.h>
# include <string.h>
# include "option.h"

typedef struct	s_digest_buffer
{
	uint8_t		r_buffer[READ_BUFFER_LEN + 1];
	uint8_t		buffer[CHUNK_SIZE + 1];
	uint32_t	len;
}				t_digest_buffer;

typedef struct	s_hash
{
	char			*cmd_name;
	char			*input_src;
	t_option		option;
	uint64_t		data_len;
	t_digest_buffer	d_buffer;
	uint32_t		result[8];
	char			output[OUTPUT_SIZE + 1];
	uint8_t			output_size;
	char			big_endian;
	void			(*cmd)(struct s_hash *, uint32_t *);
	void			(*init_cmd)(struct s_hash *);
}				t_hash;

typedef struct	s_des
{
	char			*cmd_name;
	char			*input_src;
}				t_des;

typedef struct	s_env
{
	int				argc;
	char			**argv;
	char			cmd_name[MAX_CMD_SIZE + 1];
	char			*input_src;
	t_hash			hash_env;
	t_des			des_env;
}				t_env;

int				get_hash_cmd(t_env *env);
int				get_des_cmd(t_env *env);
int				get_cmd(t_env *env, char *cmd_name, int (*getter)(t_env*));
void			ft_ssl_get_result(t_hash *hash_env);
int				ft_ssl_read(t_env *env);
void			cmd_read(t_hash *hash_env, int fd);
void			ft_ssl_string(t_hash *hash_env, char *str);
void			digest_files(t_hash *hash_env, char **filepaths, int index_max);
int				digest_string(t_hash *hash_env, char *residual_opt, int index);
void			end_digest(t_hash *hash_env);
size_t			process_buffer(t_hash *hash_env, t_digest_buffer *d_buffer,
								uint8_t *r_buffer, size_t size);
void			process_round(t_hash *hash_env, size_t start,
						size_t end, uint8_t *data);
void			fill_buffer(t_digest_buffer *d_buffer,
						uint8_t *r_buffer, size_t size);

void			format_output(t_hash *hash_env);

void			print_bit(char c, int len);
uint64_t		align_up(int n, uint64_t mod);
uint32_t		min(uint32_t a, uint32_t b);
uint32_t		byte_swap32(uint32_t x);
uint64_t		byte_swap64(uint64_t x);
void			byte_to_hexa(char *dst, uint8_t byte);
void			byte_swap32_buffer(uint32_t *buffer, size_t size);
void			print_to_upper(char *str);
int				strings_array_len(char **array);

int				error_bad_cmd(t_env *env);
int				error_illegal_opt(t_hash *hash_env, char *msg);
int				error_invalid_file(t_hash *hash_env, char *msg);
int				throw_hash_opt_error(t_hash *hash_env, int err_code);
void			error_panic(void);

#endif
