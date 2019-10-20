/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:15:47 by wta               #+#    #+#             */
/*   Updated: 2019/10/20 18:44:15 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"

static void	print_outputln(t_env *env)
{
	write(STDOUT_FILENO, env->output, env->output_size);
	write(STDOUT_FILENO, "\n", 1);
}

static void	print_reverse_output(t_env *env)
{
	print_outputln(env);
	ft_putstr(option_has(&env->option, OPT_STRING) ? " \"" : " ");
	ft_putstr(env->input_src);
	ft_putendl(option_has(&env->option, OPT_STRING) ? "\"" : "");
}

static void	print_output(t_env *env)
{
	print_to_upper(env->cmd_name);
	ft_putstr(option_has(&env->option, OPT_STRING) ? " (\"" : " (");
	ft_putstr(env->input_src);
	ft_putstr(option_has(&env->option, OPT_STRING) ? "\") = " : ") = ");
	print_outputln(env);
}

void		format_output(t_env *env)
{
	t_option *opt;

	opt = &env->option;
	if (option_has(opt, OPT_QUIET))
		print_outputln(env);
	else if (option_has(opt, OPT_PRINT) && !(option_has(opt, OPT_ISFILE)))
	{
		if (env->input)
			write(STDOUT_FILENO, env->input, ft_strlen(env->input));
		print_outputln(env);
	}
	else if (option_has(opt, OPT_ISFILE) || option_has(opt, OPT_STRING))
	{
		if (option_has(opt, OPT_REVERSE))
			print_reverse_output(env);
		else
			print_output(env);
	}
	else
		print_outputln(env);
	ft_memdel((void**)&env->input);
}
