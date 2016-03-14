/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:01:25 by scollon           #+#    #+#             */
/*   Updated: 2016/03/14 12:16:59 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	open_error_log(void)
{
	int		fd;
	time_t	epoch;
	char	*tmp;
	char	*date;
	char	*hour;

	fd = open("errors.log", O_WRONLY | O_CREAT | O_APPEND, FILE_RIGHTS);
	if (fd == -1)
		return (-1);
	else
	{
		time(&epoch);
		tmp = ft_strdup("%d/%m/%Y");
		date = ft_strnew(128);
		strftime(date, 128, tmp, localtime(&epoch));
		ft_strdel(&tmp);
		tmp = ft_strdup("%H:%M:%S");
		hour = ft_strnew(128);
		strftime(hour, 128, tmp, localtime(&epoch));
		ft_strdel(&tmp);
		ft_printf_fd(fd, "Error: %s [%s] - ", date, hour);
		ft_strdel(&hour);
		ft_strdel(&date);
		return (fd);
	}
}

static void	write_error_log(char *type, char *esrc)
{
	int		fd;
	char	*err;

	err = NULL;
	if ((fd = open_error_log()) == -1)
		return ;
	ft_printf_fd(fd, "%s", type);
	if (esrc != NULL)
	{
		err = ft_strtrim(esrc);
		ft_printf_fd(fd, ": \"%s\"", err);
		ft_strdel(&err);
	}
	ft_printf_fd(fd, "\n");
	close(fd);
}

void		error(char *type, char *esrc, short ext)
{
	char	*err;

	err = NULL;
	write_error_log(type, esrc);
	ft_printf_fd(2, "rt: %s", type);
	if (esrc != NULL)
	{
		err = ft_strtrim(esrc);
		ft_printf_fd(2, ": \"%s\"", err);
		ft_strdel(&err);
	}
	ft_printf_fd(2, "\n");
	if (ext == 1)
		exit(0);
}
