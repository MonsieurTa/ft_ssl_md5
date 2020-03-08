/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:10 by wta               #+#    #+#             */
/*   Updated: 2020/03/08 19:58:44 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_getopt.h"
#include "ft_ssl.h"
#include "md5.h"
#include "sha.h"
#include "option.h"
#include "des.h"

#include "ft_printf.h"

static int	(*g_hash_cmds[])(t_hash *, char *) = {
	set_md5,
	set_sha1,
	set_sha224,
	set_sha256,
	NULL
};

static int	(*g_des_cmds[])(t_des *, char *) = {
	set_des_cbc,
	NULL
};

static void	process_cli(t_hash *hash_env, int argc, char **argv)
{
	int	files_index;

	if (argc > 2)
	{
		hash_env->option.opt_count = argc - 2;
		hash_env->option.opt_list = &argv[2];
		files_index = manage_options(hash_env);
		hash_env->option.opts ^= (hash_env->option.opts & OPT_STRING);
		if (files_index != -1)
			digest_files(hash_env, &argv[files_index], argc - files_index);
		else if (option_has(&hash_env->option, OPT_REVERSE)
		|| option_has(&hash_env->option, OPT_QUIET))
			cmd_read(hash_env, STDIN_FILENO);
	}
	else if (argc == 2)
		cmd_read(hash_env, STDIN_FILENO);
}

int			get_hash_cmd(t_env *env)
{
	t_hash	*hash_env;
	size_t	i;

	i = 0;
	hash_env = &env->hash_env;
	while (g_hash_cmds[i] && g_hash_cmds[i](hash_env, env->cmd_name) == 0)
		i++;
	if (!g_hash_cmds[i])
		return (0);
	hash_env->cmd_name = env->cmd_name;
	process_cli(hash_env, env->argc, env->argv);
	return (1);
}

int			des_getopt(t_des *des_env, int argc, char **argv)
{
	char	c;

	while ((c = ft_getopt(argc - 1, argv + 1, "adei:k:o:p:s:v:")) != -1)
	{
		if (c == 'a')
			des_env->opt |= BASE64_OPT;
		else if (c == 'd')
			des_env->opt |= ENCRYPT_OPT;
		else if (c == 'e')
			des_env->opt |= DECRYPT_OPT;
		else if (c == 'i')
			des_env->input = g_optarg;
		else if (c == 'k')
			des_env->key = g_optarg;
		else if (c == 'o')
			des_env->output = g_optarg;
		else if (c == 'p')
			des_env->opt |= PASSWORD_OPT;
		else if (c == 's')
			des_env->salt_arg = g_optarg;
		else if (c == 'v')
			des_env->opt |= INIT_VECTOR_OPT;
		else
			return (0);
	}
	return (1);
}

void	to_upper_case(char *str)
{
	uint32_t	len;
	uint32_t	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
}

uint8_t	char_to_byte(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (0);
}

uint8_t	strbyte_to_byte(char *byte)
{
	return (char_to_byte(byte[0]) << 4 | char_to_byte(byte[1]));
}

void	str_to_bytes(uint8_t dst[], char *src)
{
	uint32_t	len;
	uint32_t	i;

	len = min((ft_strlen(src) + 2 - 1) / 2, SALT_SIZE);
	i = 0;
	while (i < len)
	{
		dst[i] = strbyte_to_byte(src + i * 2);
		i++;
	}
}

void		format_salt(t_des *des_env)
{
	if (des_env->salt_arg)
	{
		to_upper_case(des_env->salt_arg);
		str_to_bytes(des_env->salt, des_env->salt_arg);
	}
}

int			get_des_cmd(t_env *env)
{
	t_des	*des_env;
	size_t	i;

	i = 0;
	des_env = &env->des_env;
	while (g_des_cmds[i] && g_des_cmds[i](des_env, env->cmd_name) == 0)
		i++;
	if (!g_des_cmds[i])
		return (0);
	des_env->cmd_name = env->cmd_name;
	if (!des_getopt(des_env, env->argc, env->argv))
		return (-1);
	format_salt(des_env);
	pbkdf1(des_env);
	return (1);
}

int			get_cmd(t_env *env, char *cmd_name, int (*getter)(t_env*))
{
	ft_memcpy(env->cmd_name, cmd_name, min(MAX_CMD_SIZE, ft_strlen(cmd_name)));
	return (getter(env));
}

int			main(int argc, char *argv[])
{
	t_env	env;
	int		ret;

	ft_bzero(&env, sizeof(t_env));
	env.argc = argc;
	env.argv = argv;
	if (argc > 1)
	{
		ret = get_cmd(&env, argv[1], get_hash_cmd);
		if (ret == 0)
			ret = get_cmd(&env, argv[1], get_des_cmd);
		if (ret == 0)
			error_bad_cmd(&env);
	}
	else
	{
		while (1)
			ft_ssl_read(&env);
	}
}
