/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_import.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:52:16 by scollon           #+#    #+#             */
/*   Updated: 2016/03/11 11:04:34 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void	read_viewer(t_img *img, int fd, int h)
{
	char	*line;
	int		i;
	int		len;
	int		ret;

	i = -1;
	len = img->sl * h;
	if (!(line = malloc(sizeof(char) * len)))
		error(E_MALLOC, NULL, 1);
	if ((ret = read(fd, line, len)) == -1)
		error(strerror(errno), NULL, 1);
	while (++i < len)
		img->img[i] = line[i];
	ft_strdel(&line);
}

static void	viewer_info(int fd, int *w, int *h)
{
	char	*line;
	char	*del;
	char	buf[2];
	int		i;
	int		ret;

	i = 0;
	(line = ft_strnew(1)) == NULL ? error(E_MALLOC, NULL, 1) : 0;
	while (i < 2 && (ret = read(fd, buf, 1)))
	{
		ret == -1 ? error(strerror(errno), NULL, 1) : 0;
		buf[ret] = '\0';
		del = line;
		line = ft_strjoin(line, buf);
		ft_strdel(&del);
		if (buf[0] == '\n')
		{
			i == 0 ? *w = ft_atoi(line) : 0;
			i == 1 ? *h = ft_atoi(line) : 0;
			ft_strdel(&line);
			(line = ft_strnew(1)) == NULL ? error(E_MALLOC, NULL, 1) : 0;
			i++;
		}
	}
	ft_strdel(&line);
}

static void	format_check(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (ft_strcmp(str + len - 4, ".mlx") != 0)
		error("invalid format file", str, 1);
}

t_img		viewer_import(t_env *e)
{
	int		fd;
	t_img	img;

	format_check(e->viewer_path);
	if ((fd = open(e->viewer_path, O_RDWR)) == -1)
		error(strerror(errno), e->viewer_path, 1);
	viewer_info(fd, &img.w, &img.h);
	if (!(img.adr = mlx_new_image(e->mlx, img.w, img.h)))
		error(E_IMG_INIT, NULL, 1);
	if (!(img.img = mlx_get_data_addr(img.adr, &img.bpp, &img.sl, &img.endian)))
		error(E_IMG_INIT, NULL, 1);
	read_viewer(&img, fd, img.h);
	close(fd) == -1 ? error(strerror(errno), NULL, 1) : 0;
	return (img);
}
