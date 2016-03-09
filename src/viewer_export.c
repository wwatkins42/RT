/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:52:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/09 16:15:48 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*set_file_name(void)
{
	char		*file_name;
	time_t		epoch;

	time(&epoch);
	file_name = malloc(sizeof(char) * 100);
	strftime(file_name, 50, "%d_%m_%Y_%X", gmtime(&epoch));
	file_name = ft_strjoin(IMG_PATH, file_name);
	file_name = ft_strjoin(file_name, IMG_EXTENSION);
	printf("file: %s\n", file_name);
	return (file_name);
}

void		viewer_export(t_env *e)
{
	char		*file_name;
	int			len;
	int			fd;

	file_name = set_file_name();
	if ((fd = open(file_name, O_WRONLY | O_CREAT)) == -1)
		error(strerror(errno), file_name, 1);
	ft_strdel(&file_name);
	len = e->img.sl * e->win.h;
	ft_putnbr_fd(e->win.w, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(e->win.h, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(e->img.bpp, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(e->img.sl, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(e->img.endian, fd);
	write(fd, "\n", 1);
	write(fd, e->img.img, len);
	close(fd) == -1 ? error(strerror(errno), NULL, 1) : 0;
}
