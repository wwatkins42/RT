/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 23:36:24 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/26 17:34:54 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* solve_quartic.c - finds the real roots of
 *  x^4 + a x^3 + b x^2 + c x + d = 0
 */


#include "rt.h"

#define SWAPD(a,b) do { double tmp = b ; b = a ; a = tmp ; } while(0)

int
gsl_poly_solve_quartic (double a, double b, double c, double d,
                        double *x0, double *x1, double *x2, double *x3)
{
  /*
   * This code is based on a simplification of
   * the algorithm from zsolve_quartic.c for real roots
   */
  double u[3];
  double aa, pp, qq, rr, rc, sc, tc, mt;
  double w1r, w1i, w2r, w2i, w3r;
  double v[3], v1, v2, arg, theta;
  double disc, h;
  int k1, k2;
  double zarr[4];

  /* Deal easily with the cases where the quartic is degenerate. The
   * ordering of solutions is done explicitly. */
  if (0 == b && 0 == c)
    {
      if (0 == d)
        {
          if (a > 0)
            {
              *x0 = -a;
              *x1 = 0.0;
              *x2 = 0.0;
              *x3 = 0.0;
            }
          else
            {
              *x0 = 0.0;
              *x1 = 0.0;
              *x2 = 0.0;
              *x3 = -a;
            }
          return 4;
        }
      else if (0 == a)
        {
          if (d > 0)
            {
              return 0;
            }
          else
            {
              *x1 = sqrt (sqrt (-d));
              *x0 = -(*x1);
              return 2;
            }
        }
    }

  if (0.0 == c && 0.0 == d)
    {
      *x0=0.0;
      *x1=0.0;
      if (gsl_poly_solve_quadratic(1.0,a,b,x2,x3)==0) {
	mt=3;
      } else {
	mt=1;
      }
    }
  else
    {
      /* For non-degenerate solutions, proceed by constructing and
       * solving the resolvent cubic */
      aa = a * a;
      pp = b - (3.0/8.0) * aa;
      qq = c - (1.0/2.0) * a * (b - (1.0/4.0) * aa);
      rr = d - (1.0/4.0) * (a * c - (1.0/4.0) * aa * (b - (3.0/16.0) * aa));
      rc = (1.0/2.0) * pp;
      sc = (1.0/4.0) * ((1.0/4.0) * pp * pp - rr);
      tc = -((1.0/8.0) * qq * (1.0/8.0) * qq);

      /* This code solves the resolvent cubic in a convenient fashion
       * for this implementation of the quartic. If there are three real
       * roots, then they are placed directly into u[].  If two are
       * complex, then the real root is put into u[0] and the real
       * and imaginary part of the complex roots are placed into
       * u[1] and u[2], respectively. Additionally, this
       * calculates the discriminant of the cubic and puts it into the
       * variable disc. */
      {
	double qcub = (rc * rc - 3 * sc);
	double rcub = (2 * rc * rc * rc - 9 * rc * sc + 27 * tc);

	double Q = qcub / 9;
	double R = rcub / 54;

	double Q3 = Q * Q * Q;
	double R2 = R * R;

	double CR2 = 729 * rcub * rcub;
	double CQ3 = 2916 * qcub * qcub * qcub;

	disc = (CR2 - CQ3) / 2125764.0;

	if (0 == R && 0 == Q)
	  {
	    u[0] = -rc / 3;
	    u[1] = -rc / 3;
	    u[2] = -rc / 3;
	  }
	else if (CR2 == CQ3)
	  {
	    double sqrtQ = sqrt (Q);
	    if (R > 0)
	      {
		u[0] = -2 * sqrtQ - rc / 3;
		u[1] = sqrtQ - rc / 3;
		u[2] = sqrtQ - rc / 3;
	      }
	    else
	      {
		u[0] = -sqrtQ - rc / 3;
		u[1] = -sqrtQ - rc / 3;
		u[2] = 2 * sqrtQ - rc / 3;
	      }
	  }
	else if (CR2 < CQ3)
	  {
	    double sqrtQ = sqrt (Q);
	    double sqrtQ3 = sqrtQ * sqrtQ * sqrtQ;
	    double theta = acos (R / sqrtQ3);
	    if (R / sqrtQ3 >= 1.0) theta = 0.0;
	    {
	      double norm = -2 * sqrtQ;

	      u[0] = norm * cos (theta / 3) - rc / 3;
	      u[1] = norm * cos ((theta + 2.0 * M_PI) / 3) - rc / 3;
	      u[2] = norm * cos ((theta - 2.0 * M_PI) / 3) - rc / 3;
	    }
	  }
	else
	  {
	    double sgnR = (R >= 0 ? 1 : -1);
	    double modR = fabs (R);
	    double sqrt_disc = sqrt (R2 - Q3);
	    double A = -sgnR * pow (modR + sqrt_disc, 1.0 / 3.0);
	    double B = Q / A;
	    double mod_diffAB = fabs (A - B);

	    u[0] = A + B - rc / 3;
	    u[1] = -0.5 * (A + B) - rc / 3;
	    u[2] = -(sqrt (3.0) / 2.0) * mod_diffAB;
	  }
      }
      /* End of solution to resolvent cubic */

      /* Combine the square roots of the roots of the cubic
       * resolvent appropriately. Also, calculate 'mt' which
       * designates the nature of the roots:
       * mt=1 : 4 real roots (disc == 0)
       * mt=2 : 0 real roots (disc < 0)
       * mt=3 : 2 real roots (disc > 0)
       */

      if (0.0 == disc)
	u[2] = u[1];

      if (0 >= disc)
	{
	  mt = 2;

	  /* One would think that we could return 0 here and exit,
	   * since mt=2. However, this assignment is temporary and
	   * changes to mt=1 under certain conditions below.
	   */

	  v[0] = fabs (u[0]);
	  v[1] = fabs (u[1]);
	  v[2] = fabs (u[2]);

	  v1 = GSL_MAX (GSL_MAX (v[0], v[1]), v[2]);
	  /* Work out which two roots have the largest moduli */
	  k1 = 0, k2 = 0;
	  if (v1 == v[0])
	    {
	      k1 = 0;
	      v2 = GSL_MAX (v[1], v[2]);
	    }
	  else if (v1 == v[1])
	    {
	      k1 = 1;
	      v2 = GSL_MAX (v[0], v[2]);
	    }
	  else
	    {
	      k1 = 2;
	      v2 = GSL_MAX (v[0], v[1]);
	    }

	  if (v2 == v[0])
	    {
	      k2 = 0;
	    }
	  else if (v2 == v[1])
	    {
	      k2 = 1;
	    }
	  else
	    {
	      k2 = 2;
	    }

	  if (0.0 <= u[k1])
	    {
	      w1r=sqrt(u[k1]);
	      w1i=0.0;
	    }
	  else
	    {
	      w1r=0.0;
	      w1i=sqrt(-u[k1]);
	    }
	  if (0.0 <= u[k2])
	    {
	      w2r=sqrt(u[k2]);
	      w2i=0.0;
	    }
	  else
	    {
	      w2r=0.0;
	      w2i=sqrt(-u[k2]);
	    }
	}
      else
	{
	  mt = 3;

	  if (0.0 == u[1] && 0.0 == u[2])
	    {
	      arg = 0.0;
	    }
	  else
	    {
	      arg = sqrt(sqrt(u[1] * u[1] + u[2] * u[2]));
	    }
	  theta = atan2(u[2], u[1]);

	  w1r = arg * cos(theta / 2.0);
	  w1i = arg * sin(theta / 2.0);
	  w2r = w1r;
	  w2i = -w1i;
	}

      /* Solve the quadratic to obtain the roots to the quartic */
      w3r = qq / 8.0 * (w1i * w2i - w1r * w2r) /
	(w1i * w1i + w1r * w1r) / (w2i * w2i + w2r * w2r);
      h = a / 4.0;

      zarr[0] = w1r + w2r + w3r - h;
      zarr[1] = -w1r - w2r + w3r - h;
      zarr[2] = -w1r + w2r - w3r - h;
      zarr[3] = w1r - w2r - w3r - h;

      /* Arrange the roots into the variables z0, z1, z2, z3 */
      if (2 == mt)
        {
          if (u[k1] >= 0 && u[k2] >= 0)
            {
              mt = 1;
	      *x0 = zarr[0];
	      *x1 = zarr[1];
	      *x2 = zarr[2];
	      *x3 = zarr[3];
            }
	  else
	    {
	      return 0;
	    }
	}
      else
        {
	  *x0 = zarr[0];
	  *x1 = zarr[1];
        }
    }

  /* Sort the roots as usual */
  if (1 == mt)
    {
      /* Roots are all real, sort them by the real part */
      if (*x0 > *x1)
        SWAPD (*x0, *x1);
      if (*x0 > *x2)
        SWAPD (*x0, *x2);
      if (*x0 > *x3)
        SWAPD (*x0, *x3);

      if (*x1 > *x2)
        SWAPD (*x1, *x2);
      if (*x2 > *x3)
        {
          SWAPD (*x2, *x3);
          if (*x1 > *x2)
            SWAPD (*x1, *x2);
        }
      return 4;
    }
  else
    {
      /* 2 real roots */
      if (*x0 > *x1)
        SWAPD (*x0, *x1);
    }

  return 2;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 23:36:24 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/22 02:22:54 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		solve_quadratic(t_poly4 *p)
{
	double	delta;

	if (p->a2 == 0)
	{
		if (p->a1 == 0)
			return (0);
		else
		{
			p->root1 = -p->a0 / p->a1;
			return (1);
		}
	}
	delta = p->a1 * p->a1 - 4 * p->a2 * p->a0;
	if (delta < 0)
		return (0);
	else
	{
		p->root1 = (-p->a1 - sqrt(delta)) / 2 * p->a2;
		p->root2 = (-p->a1 + sqrt(delta)) / 2 * p->a2;
		return (1);
	}
}

int	solve_cubic(t_poly4 *p)
{
	double	q;
	double	qqq;
	double	r;
	double	rr;
	double	b;
	double	c;
	double	d;

	if (fabsl(p->a3) < EPSILON)
		return (solve_quadratic(p));
	d = p->a0 / p->a3;
	c = p->a1 / p->a3;
	b = p->a2 / p->a3;
	q = (b * b - c * 3) / 9;
	qqq = q * q * q;
	r = (2 * b * b * b - 9 * b * c + 27 * d) / 54;
	rr = r * r;
	if (rr < qqq)
	{
		double	theta = acos(r / sqrt(qqq));
		p->root1 = -2 * sqrt(q);
		p->root2 = -2 * sqrt(q);
		p->root3 = -2 * sqrt(q);
		p->root1 *= cos(theta / 3);
		p->root2 *= cos((theta + 2 * M_PI) / 3);
		p->root3 *= cos((theta - 2 * M_PI) / 3);
		p->root1 -= b / 3;
		p->root2 -= b / 3;
		p->root3 -= b / 3;
		return (3);
	}
	else
	{
		double	a2 = -cbrt(fabsl(r) + sqrt(rr - qqq));
		if (a2 != 0)
		{
			if (r < 0)
				a2 = -a2;
			p->root1 = a2 + q / a2;
		}
		p->root1 -= b / 3;
		return (1);
	}
	return (0);
}

int	solve_quartic(t_poly4 *p4)
{
	double	b;
	double	c;
	double	d;
	double	e;
	double	bb;
	double	i;
	double	j;
	double	k;
	t_poly4	p3;
	t_poly4	p2;
	double	z;
	int		fr = 0;
	int		far = 0;

	b = p4->a3 / p4->a4;
	c = p4->a2 / p4->a4;
	d = p4->a1 / p4->a4;
	e = p4->a0 / p4->a4;
	bb = b * b;
	i = -3 * bb * 0.125 + c; // P
	j = bb * b * 0.125 - b * c * 0.5 + d; // Q
//	 if (i > 0 || j > 0)
//		return (0);
	k = -3 * bb * bb / 256 + c * bb / 16 - b * d * 0.25 + e;
	p3.a3 = 1;
	p3.a2 = 2 * i;
	p3.a1 = i * i - 4 * k;
	p3.a0 = -j * j;
	solve_cubic(&p3);
	z = p3.root1;
	double	p = sqrt(z);
	double	r = -p;
	double	q = (i + z - j / p) / 2;
	double	s = (i + z + j / p) / 2;

	p2.a2 = 1;
	p2.a1 = p;
	p2.a0 = q;
	if ((fr = solve_quadratic(&p2)))
	{
		p4->root1 = p2.root1 - b / 4;
		p4->root2 = p2.root2 - b / 4;
	}
	p2.a2 = 1;
	p2.a1 = r;
	p2.a0 = s;
	if ((far = solve_quadratic(&p2)))
	{
		if (fr == 0)
		{
			p4->root1 = p2.root1 - b / 4;
			p4->root2 = p2.root2 - b / 4;
		}
		else
		{
			p4->root3 = p2.root1 - b / 4;
			p4->root4 = p2.root2 - b / 4;
		}
	}
	if (isnan(p4->root1))
		return (0);
	return ((fr + far) * 2);
}
