/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_exporter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 07:50:15 by scollon           #+#    #+#             */
/*   Updated: 2016/03/11 11:58:13 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_exporter.h"
#include "viewer.h"
#include <time.h>

static char	*get_full_name(char *name)
{
	time_t	epoch;
	char	*del;
	char	*buffer;
	char	*full_name;

	time(&epoch);
	buffer = ft_strdup(name);
	del = buffer;
	buffer = ft_strrchr(buffer, '/');
	buffer[ft_strrchr(buffer, '.') - buffer] = '\0';
	buffer = ft_strjoin(buffer, "_%d_%m_%Y_%H-%M-%S");
	ft_strdel(&del);
	full_name = (char *)malloc(sizeof(char) * 128);
	strftime(full_name, 128, buffer, localtime(&epoch));
	ft_strdel(&buffer);
	del = full_name;
	if (!(full_name = ft_strjoin(IMG_LOCATION, full_name)))
		error(E_MALLOC, NULL, 1);
	ft_strdel(&del);
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

static char	*create_img(t_img *img, t_infos *h_infos)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	i = h_infos->image_size - 1;
	j = 0;
	copy = (char*)malloc(sizeof(char) * h_infos->image_size);
	while (i >= 0)
	{
		i -= img->sl;
		k = 0;
		while (k < img->sl)
		{
			copy[j] = img->img[i + k + 1];
			copy[j + 1] = img->img[i + k + 2];
			copy[j + 2] = img->img[i + k + 3];
			j += 3;
			k += 4;
		}
	}
	return (copy);
}

void		bmp_exporter(t_img *img, char *name)
{
	int			i;
	int			fd;
	char		*pixel_data;
	t_header	header;
	t_infos		h_infos;

	i = 0;
	name = get_full_name(name);
	if ((fd = open(name, O_WRONLY | O_CREAT, OPEN_FLAG)) == -1)
	{
		error(strerror(errno), name, 0);
		return ;
	}
	ft_strdel(&name);
	create_header(&header, &h_infos, *img);
	write_header(fd, header, h_infos);
	pixel_data = create_img(img, &h_infos);
	write(fd, pixel_data, h_infos.image_size);
	ft_strdel(&pixel_data);
	close(fd) == -1 ? error(strerror(errno), "close", 0) : 0;
}
