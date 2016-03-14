/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yml_exporter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 09:30:41 by scollon           #+#    #+#             */
/*   Updated: 2016/03/14 08:15:12 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_full_name(char *name)
{
	char	*del;
	char	*f_name;
	char	*buffer;
	time_t	epoch;

	time(&epoch);
	!(buffer = ft_strdup(name)) ? error(E_MALLOC, NULL, 1) : 0;
	buffer[ft_strrchr(buffer, '.') - buffer] = '\0';
	del = buffer;
	if (!(buffer = ft_strjoin(buffer, "_%d_%m_%Y_%H-%M-%S")))
		error(E_MALLOC, NULL, 1);
	ft_strdel(&del);
	!(f_name = ft_strnew(128)) ? error(E_MALLOC, NULL, 1) : 0;
	strftime(f_name, 128, buffer, localtime(&epoch));
	ft_strdel(&buffer);
	del = f_name;
	!(f_name = ft_strjoin(f_name, ".yml")) ? error(E_MALLOC, NULL, 1) : 0;
	ft_strdel(&del);
	return (f_name);
}

void		yml_exporter(t_env *e, char *name)
{
	int		fd;
	char	*f_name;

	f_name = get_full_name(name);
	if ((fd = open(f_name, FILE_ARG, FILE_RIGHTS)) == -1)
	{
		error(strerror(errno), f_name, 0);
		ft_strdel(&f_name);
		return ;
	}
	ft_strdel(&f_name);
	write(fd, "---\n", 4);
	export_camera(fd, e);
	export_light(fd, e);
	export_object(fd, e);
	write(fd, "...\n", 4);
	close(fd) == -1 ? error(strerror(errno), NULL, 0) : 0;
}
