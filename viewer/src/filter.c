/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:18:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/10 18:34:16 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	img_iter(t_env *e, void (*f)(char *, char *, char *))
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = e->current->img.sl * e->current->img.h;
	if (e->current->img.img == NULL || f == NULL)
		return ;
	while (i < len)
	{
		if (i + 4 < len)
			f(&e->current->img.img[i], &e->current->img.img[i + 1],
				&e->current->img.img[i + 2]);
		i += 4;
	}
}

void	invert(char *r, char *g, char *b)
{
	*r = 255 - *r;
	*g = 255 - *g;
	*b = 255 - *b;
}
