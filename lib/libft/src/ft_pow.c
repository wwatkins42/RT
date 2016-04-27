/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 10:50:36 by aacuna            #+#    #+#             */
/*   Updated: 2016/04/25 15:05:11 by aacuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double nb, int expo)
{
	double result;

	result = 1;
	while (expo > 0)
	{
		result = result * nb;
		expo--;
	}
	while (expo < 0)
	{
		result = result / nb;
		expo++;
	}
	return (result);
}
