/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_object_type.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 11:44:10 by scollon           #+#    #+#             */
/*   Updated: 2016/05/01 12:06:35 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_OBJECT_TYPE_H
# define G_OBJECT_TYPE_H

	typedef struct		s_gobj_type
	{
		short			index;
		char			*reference;
	}					t_gobj_type;

	extern	const t_gobj_type	G_OBJECT_TYPE[20];

#endif
