/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:07:13 by wta               #+#    #+#             */
/*   Updated: 2019/05/16 00:02:44 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

t_list	*get_file(t_list_info *list, int fd)
{
	t_list	*node;
	t_gnl	new;

	node = list->head;
	while (node != NULL)
	{
		if (((t_gnl *)node->content)->fd == fd)
			return (node);
		node = node->next;
	}
	ft_bzero(&new, sizeof(t_gnl));
	new.fd = fd;
	if ((node = ft_lstnew(&new, sizeof(t_gnl))) == NULL)
		return (NULL);
	ft_pushback(list, node);
	return (node);
}

int		read_fd(char **str, int fd)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	ft_bzero(buf, BUFF_SIZE + 1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (*str == NULL)
		{
			if ((*str = ft_strdup(buf)) == NULL)
				return (-1);
		}
		else if ((*str = ft_strjoindel(*str, buf)) == NULL)
			return (-1);
		if (ft_strchr(buf, '\n') != NULL)
			return (1);
	}
	return (0);
}

int		process_line(char **str, char **line)
{
	char	*needle;
	char	*tmp;

	if (*str == NULL)
		return (0);
	if ((needle = ft_strchr(*str, '\n')) != NULL)
		*needle++ = '\0';
	if ((*line = ft_strdup(*str)) == NULL)
		return (-1);
	if (needle != NULL)
	{
		tmp = *str;
		*str = (*needle == '\0') ? NULL : ft_strdup(needle);
		ft_strdel(&tmp);
	}
	else
		ft_strdel(str);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list_info	list;
	t_list				*file;
	int					ret;

	if (fd < 0 || line == NULL || read(fd, 0, 0) < 0)
	{
		ft_listdel(&list);
		return (-1);
	}
	if ((file = get_file(&list, fd)) == NULL)
		return (-1);
	if ((ret = read_fd(&(((t_gnl*)file->content)->str),
			(((t_gnl*)file->content)->fd))) == -1)
		return (-1);
	if ((ret = process_line(&(((t_gnl*)file->content)->str), line)) == -1)
		return (-1);
	if (ret == 0)
		ft_delnode(&list, file);
	return (ret);
}
