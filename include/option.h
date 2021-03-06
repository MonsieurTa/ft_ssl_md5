/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:16:36 by wta               #+#    #+#             */
/*   Updated: 2020/02/22 14:48:39 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

# define OPT_QUIET      0x1
# define OPT_REVERSE    0x2
# define OPT_PRINT      0x4
# define OPT_STRING     0x8
# define OPT_ISFILE     0x10

typedef struct s_hash	t_hash;

typedef struct	s_option
{
	int		opt_count;
	char	**opt_list;
	char	opts;
	char	curr_opt;
	char	residual_opt : 1;
}				t_option;

int				manage_options(t_hash *hash_env);
int				option_has(t_option *option, int opt);

#endif
