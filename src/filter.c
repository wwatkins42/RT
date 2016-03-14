/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 10:41:39 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 11:03:00 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	image_filter(t_img *img, t_filter *filter,
					void (*f)(t_filter *filter, char *, char *, char *))
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = img->sl * img->h;
	if (img->img == NULL || f == NULL)
		return ;
	while (i < len)
	{
		if (i + 4 < len)
			f(filter, &img->img[i], &img->img[i + 1],
				&img->img[i + 2]);
		i += 4;
	}
}

void	invert(t_filter *filter, char *r, char *g, char *b)
{
	if (filter->invert)
	{
		*r = 255 - *r;
		*g = 255 - *g;
		*b = 255 - *b;
	}
}
