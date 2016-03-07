/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:54:22 by wwatkins          #+#    #+#             */
/*   Updated: 2016/01/03 12:52:44 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new;

	i = -1;
	if (!(new = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[++i] != '\0')
		new[i] = f(i, s[i]);
	new[i] = '\0';
	return (new);
}
