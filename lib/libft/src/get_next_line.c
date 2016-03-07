/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:24:06 by scollon           #+#    #+#             */
/*   Updated: 2016/02/01 09:26:38 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_line(int const fd, char **line, char **r, char *el)
{
	char *del;

	if (el)
	{
		del = r[fd];
		*line = ft_strsub(r[fd], 0, el - r[fd]);
		r[fd] = ft_strsub(r[fd], el - r[fd] + 1, ft_strlen(r[fd]));
		ft_strdel(&del);
	}
	else
	{
		*line = ft_strdup(r[fd]);
		ft_strdel(&r[fd]);
	}
}

int			get_next_line(int const fd, char **line)
{
	int				ret;
	char			*del;
	char			*el;
	char			buf[BUFF_SIZE + 1];
	static char		*r[256];

	if (!line || fd < 0 || fd > 256 || BUFF_SIZE < 1)
		return (-1);
	if (!(r[fd] = (r[fd] == NULL ? ft_strnew(1) : r[fd])))
		return (-1);
	while ((el = ft_strchr(r[fd], '\n')) &&
		(ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		del = r[fd];
		r[fd] = ft_strjoin(r[fd], buf);
		ft_strdel(&del);
	}
	if (ret == -1)
		return (-1);
	fill_line(fd, line, r, el);
	return (1);
}
