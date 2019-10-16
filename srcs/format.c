/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:15:47 by wta               #+#    #+#             */
/*   Updated: 2019/10/16 17:32:20 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"

static void	print_reverse_output(t_env *env)
{
	ft_putstr(env->output);
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
	ft_putendl(env->output);
}
#include <stdio.h>
void	format_output(t_env *env)
{
	t_option *opt;

	opt = &env->option;
	if (option_has(opt, OPT_QUIET))
		ft_putendl(env->output);
	else if (option_has(opt, OPT_PRINT) && !(option_has(opt, OPT_ISFILE)))
	{
		if (env->input)
			write(STDOUT_FILENO, env->input, ft_strlen(env->input));
		ft_putendl(env->output);
	}
	else if (option_has(opt, OPT_ISFILE) || option_has(opt, OPT_STRING))
	{
		if (option_has(opt, OPT_REVERSE))
			print_reverse_output(env);
		else
			print_output(env);
		opt->opts ^= OPT_STRING;
	}
	else
		ft_putendl(env->output);	
	ft_memdel((void**)&env->input);
}