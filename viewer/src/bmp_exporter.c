/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_exporter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 07:50:15 by scollon           #+#    #+#             */
/*   Updated: 2016/03/11 10:03:04 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_exporter.h"
#include "viewer.h"

static char	*get_full_name(char *name)
{
	char	*del;
	char	*full_name;

	if (!(full_name = ft_strjoin(IMG_LOCATION, name)))
		error(E_MALLOC, NULL, 1);
	del = full_name;
	if (!(full_name = ft_strjoin(full_name, IMG_FORMAT)))
		error(E_MALLOC, NULL, 1);
	ft_strdel(&del);
	return (full_name);
}

static void	create_header(t_header *header, t_infos *h_infos, t_img img)
{
	header->type[0] = 0x42;
	header->type[1] = 0x4D;
	header->file_size = 54 + (img.sl * img.h);
	header->reserved = 0x00000000;
	header->offset = 54;
	h_infos->header_size = 40;
	h_infos->height = img.h;
	h_infos->width = img.w;
	h_infos->panes = 1;
	h_infos->bpp = 24;
	h_infos->compression = 0;
	h_infos->image_size = img.sl * img.h;
	h_infos->x_res = 2835;
	h_infos->y_res = 2835;
	h_infos->nb_color = 0;
	h_infos->important_color = 0;
}

static void	write_header(const int fd, t_header header, t_infos h_infos)
{
	write(fd, &header.type, 2);
	write(fd, &header.file_size, 4);
	write(fd, &header.reserved, 4);
	write(fd, &header.offset, 4);
	write(fd, &h_infos.header_size, 4);
	write(fd, &h_infos.width, 4);
	write(fd, &h_infos.height, 4);
	write(fd, &h_infos.panes, 2);
	write(fd, &h_infos.bpp, 2);
	write(fd, &h_infos.compression, 4);
	write(fd, &h_infos.image_size, 4);
	write(fd, &h_infos.x_res, 4);
	write(fd, &h_infos.y_res, 4);
	write(fd, &h_infos.nb_color, 4);
	write(fd, &h_infos.important_color, 4);
}

void		bmp_exporter(t_img *img, char *name)
{
	int			i;
	int			fd;
	t_header	header;
	t_infos		h_infos;

	i = -4;
	name = get_full_name(name);
	if ((fd = open(name, O_WRONLY | O_CREAT, OPEN_FLAG)) == -1)
		error(strerror(errno), name, 1);
	create_header(&header, &h_infos, *img);
	write_header(fd, header, h_infos);
	while ((i += 4) < h_infos.image_size)
		write(fd, &img->img[i], 3);
	!close(fd) ? error(strerror(errno), "close", 0) : 0;
}
