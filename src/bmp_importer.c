/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_importer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 09:53:47 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/28 09:55:29 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_texture	read_header(char *file_path)
{
	t_texture	texture;
	FILE		*file;

	if ((file = fopen(file_path, "r")) == NULL)
		error(strerror(errno), file_path, 1);
	fseek(file, 18, SEEK_SET);
	fread(&texture.w, 4, 1, file);
	fread(&texture.h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&texture.bpp, 2, 1, file);
	if ((fclose(file)) != 0)
		error(strerror(errno), NULL, 1);
	texture.opp = texture.bpp / 8;
	texture.sl = texture.w * texture.opp;
	texture.defined = 1;
	texture.w < 0 ? texture.w = -texture.w : 0;
	texture.h < 0 ? texture.h = -texture.h : 0;
	return (texture);
}

static void			get_image(t_texture *texture, char *buf, int i)
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
		if ((texture->img[y] = malloc(sizeof(t_vec3) * texture->w)) == NULL)
			error(E_MALLOC, NULL, 1);
		while (j < texture->sl)
		{
			texture->img[y][x].x = (double)(buf[i + j + 2] & 0xFF) / 255.0;
			texture->img[y][x].y = (double)(buf[i + j + 1] & 0xFF) / 255.0;
			texture->img[y][x].z = (double)(buf[i + j] & 0xFF) / 255.0;
			x++;
			j += 3;
		}
		y++;
	}
}

static void			read_image(t_texture *texture, int fd)
{
	int			i;
	char		*buf;

	if ((buf = malloc(sizeof(char) * texture->sl * texture->h + 1)) == NULL)
		error(E_MALLOC, NULL, 1);
	texture->img = (t_vec3**)malloc(sizeof(t_vec3*) * texture->h);
	lseek(fd, 54, SEEK_SET);
	if ((i = read(fd, buf, texture->sl * texture->h)) == -1)
		error(strerror(errno), NULL, 1);
	get_image(texture, buf, i);
	ft_strdel(&buf);
}

t_texture			bmp_importer(char *file_path)
{
	t_texture	texture;
	int			fd;

	texture = read_header(file_path);
	texture.normal_map = 0;
	if (texture.bpp != 24)
		error("bmp bpp (bytePerPixel) not handled.", NULL, 1);
	if ((fd = open(file_path, O_RDWR)) == -1)
		error(strerror(errno), file_path, 1);
	read_image(&texture, fd);
	(close(fd)) == -1 ? error(strerror(errno), NULL, 1) : 0;
	return (texture);
}
