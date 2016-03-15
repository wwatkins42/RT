/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_importer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 09:53:47 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/15 14:05:02 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_texture	read_header(char *file_path)
{
	t_texture	texture;

	FILE *file = fopen(file_path, "r");
	fseek(file, 18, SEEK_SET);
    fread(&texture.w, 4, 1, file);
    fread(&texture.h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&texture.bpp, 2, 1, file);
	fseek(file, 54, SEEK_SET);
	fclose(file);
	texture.opp = texture.bpp / 8;
	texture.sl = texture.w * texture.opp;
	return (texture);
}

static void			read_image(t_texture *texture, int fd)
{
	int			i;
	int			j;
	int			k;
	char		*buf;

	buf = malloc(sizeof(char) * texture->sl * texture->h + 1);
	texture->img = malloc(sizeof(t_vec3) * texture->w * texture->h);
	lseek(fd, 54, SEEK_SET);
	read(fd, buf, texture->sl * texture->h);
	i = texture->sl * texture->h - 1;
	j = 0;
	while (i >= 0)
	{
		i -= texture->sl;
		k = 0;
		while (k < texture->sl)
		{
			texture->img[j].x = (float)buf[i + k] / 255.0;
			texture->img[j].y = (float)buf[i + k + 1] / 255.0;
			texture->img[j].z = (float)buf[i + k + 2] / 255.0;
			j++;
			k += 3;
		}
	}
	ft_strdel(&buf);
}

t_texture			bmp_importer(char *file_path)
{
	t_texture	texture;
	int			fd;

	texture = read_header(file_path);
	if (texture.bpp != 24)
		error("bmp bpp (bytePerPixel) not handled.", NULL, 1);
	if ((fd = open(file_path, O_RDWR)) == -1)
		error(strerror(errno), file_path, 1);
	read_image(&texture, fd);
	(close(fd)) == -1 ? error(strerror(errno), NULL, 1) : 0;
	return (texture);
}
