/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:01:25 by scollon           #+#    #+#             */
/*   Updated: 2016/03/07 17:11:28 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	error(char *type, char *esrc, short ext)
{
	ft_printf("rt: %s", type);
	if (esrc != NULL)
		ft_printf("%s", esrc);
	ft_printf("/n");
	if (ext == 1)
		exit(0);
}
