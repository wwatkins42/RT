/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_importer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 09:53:47 by wwatkins          #+#    #+#             */
/*   Updated: 2016/05/01 11:18:42 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			read_header(t_env *e, char *file_path, t_texture *texture)
{
	FILE		*file;

	if (!(file = fopen(file_path, "r")))
		error(e, strerror(errno), file_path, 1);
	fseek(file, 18, SEEK_SET);
	fread(&texture->w, 4, 1, file);
	fread(&texture->h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&texture->bpp, 2, 1, file);
	fclose(file) != 0 ? error(e, strerror(errno), NULL, 1) : 0;
	texture->opp = texture->bpp / 8;
	texture->sl = texture->w * texture->opp;
	texture->defined = 1;
	texture->w < 0 ? texture->w = -texture->w : 0;
	texture->h < 0 ? texture->h = -texture->h : 0;
}

static void			get_image(t_env *e, t_texture *texture, char *buf, int i)
{
	int	j;
	int	x;
	int	y;

	y = 0;
	while (i >= 0)
	{
		i -= texture->sl;
		j = 0;
		x = 0;
		if (!(texture->img[y] = (t_rgb*)malloc(sizeof(t_rgb) * texture->w)))
			error(e, E_MALLOC, NULL, 1);
		while (j < texture->sl)
		{
			texture->img[y][x].x = (unsigned char)(buf[i + j + 2] & 0xFF);
			texture->img[y][x].y = (unsigned char)(buf[i + j + 1] & 0xFF);
			texture->img[y][x].z = (unsigned char)(buf[i + j] & 0xFF);
			x++;
			j += 3;
		}
		y++;
	}
}

static void			read_image(t_env *e, t_texture *texture, int fd)
{
	int			i;
	char		*buf;

	if (!(buf = (char*)malloc(sizeof(char) * texture->sl * texture->h + 1)))
		error(e, E_MALLOC, NULL, 1);
	if (!(texture->img = (t_rgb**)malloc(sizeof(t_rgb*) * texture->h)))
		error(e, E_MALLOC, NULL, 1);
	lseek(fd, 54, SEEK_SET);
	if ((i = read(fd, buf, texture->sl * texture->h)) == -1)
		error(e, strerror(errno), NULL, 1);
	get_image(e, texture, buf, i);
	ft_strdel(&buf);
}

void				bmp_importer(t_env *e, char *file_path, t_texture *texture)
{
	int			fd;

	read_header(e, file_path, texture);
	texture->normal_map = 0;
	if (texture->bpp != 24)
		error(e, "bmp bpp (bytePerPixel) not handled.", NULL, 1);
	if ((fd = open(file_path, O_RDWR)) == -1)
		error(e, strerror(errno), file_path, 1);
	read_image(e, texture, fd);
	close(fd) == -1 ? error(e, strerror(errno), NULL, 1) : 0;
}
