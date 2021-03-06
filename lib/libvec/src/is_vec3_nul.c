/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_vec3_nul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:26:17 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 16:27:07 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

int		is_vec3_nul(t_vec3 v)
{
	if (v.x == 0 && v.y == 0 && v.z == 0)
		return (1);
	return (0);
}
