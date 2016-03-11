/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_exporter.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 07:52:09 by scollon           #+#    #+#             */
/*   Updated: 2016/03/11 10:06:28 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_EXPORTER_H
# define BMP_EXPORTER_H

# include "viewer.h"

# ifndef IMG_LOCATION
#  define IMG_LOCATION "./resource/images/"
# endif

# ifndef IMG_FORMAT
#  define IMG_FORMAT ".bmp"
# endif

# ifndef OPEN_FLAG
#  define OPEN_FLAG S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# endif


typedef struct			s_header
{
	char	type[2];
	int		reserved;
	int		file_size;
	int		offset;
}						t_header;

typedef struct			s_infos
{
	int		header_size;
	int		image_size;
	int		nb_color;
	int		important_color;
	int		compression;
	int		width;
	int		height;
	int		x_res;
	int		y_res;
	short	panes;
	short	bpp;
}						t_infos;

void					bmp_exporter(t_img *image, char *name);

#endif
