/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_import.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:52:16 by scollon           #+#    #+#             */
/*   Updated: 2016/03/09 16:15:36 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*read_viewer(int fd)
{
	char	*del;
	char	*line;
	char	*view;

	del = NULL;
	view = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (view == NULL)
			view = ft_strdup(line);
		else
		{
			del = view;
			if (!(view = ft_strjoin(view, line)))
				return (NULL);
			ft_strdel(&del);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (view);
}

static void	viewer_info(int fd, int *w, int *h, t_img *img)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 5)
	{
		get_next_line(fd, &line);
		i == 0 ? *w = ft_atoi(line) : 0;
		i == 1 ? *h = ft_atoi(line) : 0;
		i == 2 ? img->bpp = ft_atoi(line) : 0;
		i == 3 ? img->sl = ft_atoi(line) : 0;
		i == 4 ? img->endian = ft_atoi(line) : 0;
		ft_strdel(&line);
	}
}

t_img		viewer_import(t_env *e)
{
	int		fd;
	int		w;
	int		h;
	char	*tmp;
	t_img	img;

	if ((fd = open(e->arg.viewer_path, O_RDWR)) == -1)
		error(strerror(errno), e->arg.viewer_path, 1);
	ft_strdel(&e->arg.viewer_path);
	viewer_info(fd, &w, &h, &img);
	tmp = read_viewer(fd);
	tmp == NULL ? error(E_MALLOC, NULL, 1) : 0;
	if (!(img.adr = mlx_new_image(e->mlx, w, h)))
		error(E_IMG_INIT, NULL, 1);
	img.img = tmp;
	close(fd) == -1 ? error(strerror(errno), NULL, 1) : 0;
	return (img);
}
