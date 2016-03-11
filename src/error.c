/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:01:25 by scollon           #+#    #+#             */
/*   Updated: 2016/03/11 09:41:48 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	error(char *type, char *esrc, short ext)
{
	char	*err;

	err = NULL;
	ft_printf("rt: %s", type);
	if (esrc != NULL)
	{
		err = ft_strtrim(esrc);
		ft_printf(": \"%s\"", err);
		ft_strdel(&err);
	}
	ft_printf("\n");
	if (ext == 1)
		exit(0);
}
