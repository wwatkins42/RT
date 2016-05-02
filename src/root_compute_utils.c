/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_compute_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:00:54 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/27 18:30:07 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			swapd(double *a, double *b)
{
	double	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
	return (1);
}

void		set_d3(double *u, double u0, double u1, double u2)
{
	u[0] = u0;
	u[1] = u1;
	u[2] = u2;
}

int			deal_with_degenerate(double *a, double *r)
{
	if (a[0] == 0.)
	{
		r[0] = 0;
		r[1] = 0;
		r[2] = 0;
		r[3] = 0;
		if (a[3] > 0)
			r[0] = -a[3];
		else
			r[3] = -a[3];
		return (4);
	}
	else
	{
		if (a[0] > 0)
			return (0);
		else
		{
			r[1] = sqrt(sqrt(-a[0]));
			r[0] = -r[1];
			return (2);
		}
	}
}

static void	last_case(t_quartic *q)
{
	q->sgnbr = (q->br >= 0 ? 1 : -1);
	q->modbr = fabs(q->br);
	q->sqrt_disc = sqrt(q->br2 - q->bq3);
	q->ba = -q->sgnbr * pow(q->modbr + q->sqrt_disc, 1.0 / 3.0);
	q->bb = q->bq / q->ba;
	q->mod_diffbabb = fabs(q->ba - q->bb);
	q->u[0] = q->ba + q->bb - q->rc / 3;
	q->u[1] = -0.5 * (q->ba + q->bb) - q->rc / 3;
	q->u[2] = -(sqrt(3.0) / 2.0) * q->mod_diffbabb;
}

/*
** THIS ONE IS OK
*/

void		find_solution_to_resolvent_cubic(t_quartic *q)
{
	if (0 == q->br && 0 == q->bq)
		set_d3(q->u, -q->rc / 3, -q->rc / 3, -q->rc / 3);
	else if (q->cr2 == q->cq3)
	{
		q->sqrtbq = sqrt(q->bq);
		q->br > 0 ? set_d3(q->u, -2 * q->sqrtbq - q->rc / 3,
			q->sqrtbq - q->rc / 3,
			q->sqrtbq - q->rc / 3) : set_d3(q->u, -q->sqrtbq - q->rc / 3,
			-q->sqrtbq - q->rc / 3, 2 * q->sqrtbq - q->rc / 3);
	}
	else if (q->cr2 < q->cq3)
	{
		q->sqrtbq = sqrt(q->bq);
		q->sqrtbq3 = q->sqrtbq * q->sqrtbq * q->sqrtbq;
		q->theta = acos(q->br / q->sqrtbq3);
		if (q->br / q->sqrtbq3 >= 1.0)
			q->theta = 0.0;
		q->norm = -2 * q->sqrtbq;
		q->u[0] = q->norm * cos(q->theta / 3) - q->rc / 3;
		q->u[1] = q->norm * cos((q->theta + 2.0 * M_PI) / 3) - q->rc / 3;
		q->u[2] = q->norm * cos((q->theta - 2.0 * M_PI) / 3) - q->rc / 3;
	}
	else
		last_case(q);
}
