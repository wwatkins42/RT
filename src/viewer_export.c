/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:52:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 10:18:12 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*set_file_name(t_env *e)
{
	char		*file_name;
	char		*name;
	char		*file;
	char		*del;
	time_t		epoch;

	time(&epoch);
	name = ft_strdup(e->arg.file);
	del = name;
	name = ft_strrchr(name, '/') + 1;
	name[ft_strrchr(name, '.') - name] = '\0';
	file_name = malloc(sizeof(char) * FILE_NAME_LENGTH);
	file = ft_strjoin(name, "_%d_%m_%Y_%X");
	strftime(file_name, FILE_NAME_LENGTH, file, localtime(&epoch));
	ft_strdel(&del);
	ft_strdel(&file);
	file_name = ft_strjoin(IMG_PATH, file_name);
	file_name = ft_strjoin(file_name, IMG_EXTENSION);
	return (file_name);
}

void		viewer_export(t_env *e, t_img *img)
{
	char		*file_name;
	int			len;
	int			fd;

	(void)img;
	file_name = set_file_name(e);
	if ((fd = open(file_name, FILE_ARG, FILE_RIGHTS)) == -1)
		error(strerror(errno), file_name, 1);
	ft_strdel(&file_name);
	len = img->sl * e->win.h;
	ft_putnbr_fd(e->win.w, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(e->win.h, fd);
	write(fd, "\n", 1);
	write(fd, img->img, len);
	close(fd) == -1 ? error(strerror(errno), NULL, 1) : 0;
}
