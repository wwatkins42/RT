/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:21:13 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/27 18:50:35 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Finds the real roots of x^4 + a[3] x^3 + a[2] x^2 + a[1] x + a[0] = 0
** arranging them ordered in r and returning the number of the roots (0, 2 or 4)
*/

static void	init_stru(t_quartic *q, double *a)
{
	q->aa = a[3] * a[3];
	q->pp = a[2] - (3.0 / 8.0) * q->aa;
	q->qq = a[1] - (1.0 / 2.0) * a[3] * (a[2] - (1.0 / 4.0) * q->aa);
	q->rr = a[0] - (1.0 / 4.0) * (a[3] * a[1] - (1.0 / 4.0) * q->aa *
		(a[2] - (3.0 / 16.0) * q->aa));
	q->rc = (1.0 / 2.0) * q->pp;
	q->sc = (1.0 / 4.0) * ((1.0 / 4.0) * q->pp * q->pp - q->rr);
	q->tc = -((1.0 / 8.0) * q->qq * (1.0 / 8.0) * q->qq);
	q->qcub = (q->rc * q->rc - 3 * q->sc);
	q->rcub = (2 * q->rc * q->rc * q->rc - 9 * q->rc * q->sc + 27 * q->tc);
	q->bq = q->qcub / 9;
	q->br = q->rcub / 54;
	q->bq3 = q->bq * q->bq * q->bq;
	q->br2 = q->br * q->br;
	q->cr2 = 729 * q->rcub * q->rcub;
	q->cq3 = 2916 * q->qcub * q->qcub * q->qcub;
	q->disc = (q->cr2 - q->cq3) / 2125764.0;
	q->w1r = 0.0;
	q->w1i = 0.0;
	q->w2r = 0.0;
	q->w2i = 0.0;
}

static void	deal_with_pos_disc(t_quartic *q)
{
	q->mt = 2;
	set_d3(q->v, fabs(q->u[0]), fabs(q->u[1]), fabs(q->u[2]));
	q->v1 = fmax(fmax(q->v[0], q->v[1]), q->v[2]);
	if (q->v1 == q->v[0] && ((q->k1 = 0) || 1))
		q->v2 = fmax(q->v[1], q->v[2]);
	else if (q->v1 == q->v[1] && (q->k1 = 1))
		q->v2 = fmax(q->v[0], q->v[2]);
	else if ((q->k1 = 2))
		q->v2 = fmax(q->v[0], q->v[1]);
	if (q->v2 == q->v[0])
		q->k2 = 0;
	else if (q->v2 == q->v[1])
		q->k2 = 1;
	else
		q->k2 = 2;
	if (0.0 <= q->u[q->k1] && ((q->w1i = 0.0) || 1))
		q->w1r = sqrt(q->u[q->k1]);
	else if ((q->w1r = 0.0) || 1)
		q->w1i = sqrt(-q->u[q->k1]);
	if (0.0 <= q->u[q->k2] && ((q->w2i = 0.0) || 1))
		q->w2r = sqrt(q->u[q->k2]);
	else if ((q->w2r = 0.0) || 1)
		q->w2i = sqrt(-q->u[q->k2]);
}

static void	deal_with_neg_disc(t_quartic *q)
{
	q->mt = 3;
	if (0.0 == q->u[1] && 0.0 == q->u[2])
		q->arg = 0.0;
	else
		q->arg = sqrt(sqrt(q->u[1] * q->u[1] + q->u[2] * q->u[2]));
	q->theta = atan2(q->u[2], q->u[1]);
	q->w1r = q->arg * cos(q->theta / 2.0);
	q->w1i = q->arg * sin(q->theta / 2.0);
	q->w2r = q->w1r;
	q->w2i = -q->w1i;
}

static int	deal_with_it(t_quartic *q, double *a, double *r)
{
	init_stru(q, a);
	find_solution_to_resolvent_cubic(q);
	if (0.0 == q->disc)
		q->u[2] = q->u[1];
	if (0 >= q->disc)
		deal_with_pos_disc(q);
	else
		deal_with_neg_disc(q);
	q->w3r = q->qq / 8.0 * (q->w1i * q->w2i - q->w1r * q->w2r) /
	(q->w1i * q->w1i + q->w1r * q->w1r) / (q->w2i * q->w2i + q->w2r * q->w2r);
	q->h = a[3] / 4.0;
	q->zarr[0] = q->w1r + q->w2r + q->w3r - q->h;
	q->zarr[1] = -q->w1r - q->w2r + q->w3r - q->h;
	q->zarr[2] = -q->w1r + q->w2r - q->w3r - q->h;
	q->zarr[3] = q->w1r - q->w2r - q->w3r - q->h;
	if (2 == q->mt)
	{
		if (q->u[q->k1] >= 0 && q->u[q->k2] >= 0 && (q->mt = 1))
			fonction_relativement_assez_nulle(r, q->zarr);
		else
			return (0);
	}
	else
		set_d3(r, q->zarr[0], q->zarr[1], -1);
	return (1);
}

int			solve_quartic(double *a, double *r)
{
	t_quartic	q;

	if (a[2] == 0. && a[1] == 0. && (a[0] == 0. || a[3] == 0.))
		return (deal_with_degenerate(a, r));
	if (0.0 == a[1] && 0.0 == a[0] && ((r[0] = 0.0) || 1))
	{
		r[1] = 0.0;
		set_d3(q.args, a[2], a[3], 1);
		q.mt = ((solve_quadratic(q.args, &r[2]) == 0) ? 3 : 1);
	}
	else if (!deal_with_it(&q, a, r))
		return (0);
	if (1 == q.mt)
	{
		(r[0] > r[1]) ? swapd(&r[0], &r[1]) : 0;
		(r[0] > r[2]) ? swapd(&r[0], &r[2]) : 0;
		(r[0] > r[3]) ? swapd(&r[0], &r[3]) : 0;
		(r[1] > r[2]) ? swapd(&r[1], &r[2]) : 0;
		if (r[2] > r[3] && swapd(&r[2], &r[3]))
			(r[1] > r[2]) ? swapd(&r[1], &r[2]) : 0;
		return (4);
	}
	else if (r[0] > r[1])
		swapd(&r[0], &r[1]);
	return (2);
}
