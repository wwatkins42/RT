/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:49:34 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 11:52:35 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_clampf(double value, double min, double max)
{
	value > max ? value = max : 0;
	value < min ? value = min : 0;
	return (value);
}

int		ft_clamp(int value, int min, int max)
{
	value > max ? value = max : 0;
	value < min ? value = min : 0;
	return (value);
}
