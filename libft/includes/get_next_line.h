/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 22:10:46 by wta               #+#    #+#             */
/*   Updated: 2019/05/15 22:14:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024

# include "libft.h"

typedef struct	s_gnl
{
	char	*str;
	int		fd;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
