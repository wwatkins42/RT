/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_exporter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 07:50:15 by scollon           #+#    #+#             */
/*   Updated: 2016/04/25 09:38:48 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_full_name(char *name)
{
	time_t	epoch;
	char	*del;
	char	*buffer;
	char	*f_name;

	time(&epoch);
	!(buffer = ft_strdup(name)) ? error(E_MALLOC, NULL, 1) : 0;
	del = buffer;
	buffer = ft_strrchr(buffer, '/');
	buffer[ft_strrchr(buffer, '.') - buffer] = '\0';
	if (!(buffer = ft_strjoin(buffer, "_%d_%m_%Y_%H-%M-%S")))
		error(E_MALLOC, NULL, 1);
	ft_strdel(&del);
	!(f_name = ft_strnew(128)) ? error(E_MALLOC, NULL, 1) : 0;
	strftime(f_name, 128, buffer, localtime(&epoch));
	ft_strdel(&buffer);
	del = f_name;
	!(f_name = ft_strjoin(BMP_LOCATION, f_name)) ? error(E_MALLOC, NULL, 1) : 0;
	ft_strdel(&del);
	del = f_name;
	!(f_name = ft_strjoin(f_name, ".bmp")) ? error(E_MALLOC, NULL, 1) : 0;
	ft_strdel(&del);
	return (f_name);
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
	if (!(copy = (char*)malloc(sizeof(char) * h_infos->image_size)))
		error(E_MALLOC, NULL, 1);
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

void		bmp_exporter(t_cam *cam, char *name)
{
	int			fd;
	char		*pixel_data;
	t_img		img;
	t_header	header;
	t_infos		h_infos;

	img = cam->type == STEREOSCOPIC ? cam->stereo : cam->img;
	name = get_full_name(name);
	if ((fd = open(name, O_WRONLY | O_CREAT, OPEN_FLAG)) == -1)
	{
		error(strerror(errno), name, 0);
		return ;
	}
	ft_strdel(&name);
	create_header(&header, &h_infos, img);
	write_header(fd, header, h_infos);
	pixel_data = create_img(&img, &h_infos);
	write(fd, pixel_data, h_infos.image_size);
	ft_strdel(&pixel_data);
	close(fd) == -1 ? error(strerror(errno), "close", 0) : 0;
}
