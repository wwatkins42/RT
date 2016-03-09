/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 08:22:00 by scollon           #+#    #+#             */
/*   Updated: 2016/03/09 10:29:07 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_line(int const fd, char **line, char **r)
{
	char *del;

	if (ft_strchr(r[fd], '\n'))
	{
		del = r[fd];
		*line = ft_strsub(r[fd], 0, ft_strchr(r[fd], '\n') - r[fd]);
		r[fd] = ft_strsub(r[fd], ft_strchr(r[fd], '\n') - r[fd] + 1,
				ft_strlen(r[fd]));
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
	int			ret;
	char		*del;
	char		buf[BUFF_SIZE + 1];
	static char *r[2147483648];

	r[fd] = (r[fd] == NULL ? ft_strnew(1) : r[fd]);
	if (!line || fd < 0 || !r[fd])
		return (-1);
	while (!ft_strchr(r[fd], '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		del = r[fd];
		r[fd] = ft_strjoin(r[fd], buf);
		ft_strdel(&del);
	}
	if (ret == -1)
		return (-1);
	fill_line(fd, line, r);
	return (!r[fd] && !ft_strlen(*line) ? 0 : 1);
}
