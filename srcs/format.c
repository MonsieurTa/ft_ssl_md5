/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:15:47 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 14:47:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"

static void	print_outputln(t_hash *hash_env)
{
	write(STDOUT_FILENO, hash_env->output, hash_env->output_size);
	write(STDOUT_FILENO, "\n", 1);
}

static void	print_reverse_output(t_hash *hash_env)
{
	write(STDOUT_FILENO, hash_env->output, hash_env->output_size);
	ft_putstr(option_has(&hash_env->option, OPT_STRING) ? " \"" : " ");
	ft_putstr(hash_env->input_src);
	ft_putendl(option_has(&hash_env->option, OPT_STRING) ? "\"" : "");
}

static void	print_output(t_hash *hash_env)
{
	print_to_upper(hash_env->cmd_name);
	ft_putstr(option_has(&hash_env->option, OPT_STRING) ? " (\"" : " (");
	ft_putstr(hash_env->input_src);
	ft_putstr(option_has(&hash_env->option, OPT_STRING) ? "\") = " : ") = ");
	print_outputln(hash_env);
}

void		format_output(t_hash *hash_env)
{
	t_option *opt;

	opt = &hash_env->option;
	if (option_has(opt, OPT_QUIET))
		print_outputln(hash_env);
	else if (option_has(opt, OPT_PRINT) && !(option_has(opt, OPT_ISFILE)))
	{
		opt->opts ^= OPT_PRINT;
		print_outputln(hash_env);
	}
	else if (option_has(opt, OPT_ISFILE) || option_has(opt, OPT_STRING))
	{
		if (option_has(opt, OPT_REVERSE))
			print_reverse_output(hash_env);
		else
			print_output(hash_env);
	}
	else
		print_outputln(hash_env);
}
