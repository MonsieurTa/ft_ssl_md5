/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:12:20 by wta               #+#    #+#             */
/*   Updated: 2019/10/14 18:55:40 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_ssl.h"
#include "md5.h"
#include "ft_printf.h"

void		swap_byte(void *ptr, uint32_t size)
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

void		byte_to_hexa(char *dst, uint8_t byte)
{
	dst[0] = "0123456789abcdef"[byte >> 4];
	dst[1] = "0123456789abcdef"[byte & 0xf];
}

uint64_t	align_up(int n, uint64_t mod)
{
	uint64_t	res;

	res = n % mod;
	return res == 0 ? (
		n
	) : (n - res) + mod;
}

void		digest_file(t_env *env, char *filepath)
{
	int	fd;

	if ((fd = open(filepath, O_RDONLY)) == -1)
		exit(0);
	ft_ssl_read(env, fd);
	md5_join_result(&env->tool, env);
	md5_get_result(env);
	ft_printf("%s\n", env->result);
	close(fd);
}

void		digest_files(t_env *env, char **filepaths, int index_max)
{
	int	i;

	i = 0;
	while (i < index_max)
	{
		digest_file(env, filepaths[i]);
		i++;
	}
}
