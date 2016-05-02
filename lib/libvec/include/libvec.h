/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:26:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/05/02 18:09:22 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVEC_H
# define LIBVEC_H

# include <math.h>

# define ABS(x) (x < 0 ? -x : x)
# define PI 3.1415926
# define DEG2RAD PI / 180
# define RAD2DEG 180 / PI

enum { X, Y, Z };

typedef	struct	s_rgb
{
	unsigned char	x;
	unsigned char	y;
	unsigned char	z;
}				t_rgb;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_vec3i
{
	int		x;
	int		y;
	int		z;
}				t_vec3i;

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct	s_vec2i
{
	int		x;
	int		y;
}				t_vec2i;

t_vec2			vec2(double x, double y);
t_vec2i			vec2i(t_vec2 v);
t_vec2			vec2_add(t_vec2 va, t_vec2 vb);
t_vec2			vec2_sub(t_vec2 va, t_vec2 vb);
t_vec2			vec2_mul(t_vec2 va, t_vec2 vb);
t_vec2			vec2_fmul(t_vec2 v, double m);
double			vec2_dot(t_vec2 va, t_vec2 vb);
void			vec2_rot(t_vec2 *v, double theta);
double			vec2_magnitude(t_vec2 v);
void			vec2_normalize(t_vec2 *v);
t_vec2			vec2_scale(t_vec2 v, double scale);
t_vec3			vec3_zero(void);
t_vec3			vec3_up(void);
t_vec3			vec3_right(void);
t_vec3			vec3_forward(void);
t_vec3			vec3(double x, double y, double z);
t_vec3i			vec3i(t_vec3 v);
t_vec3			vec3_add(t_vec3 va, t_vec3 vb);
t_vec3			vec3_sub(t_vec3 va, t_vec3 vb);
t_vec3			vec3_mul(t_vec3 va, t_vec3 vb);
t_vec3			vec3_fmul(t_vec3 v, double m);
double			vec3_dot(t_vec3 va, t_vec3 vb);
void			vec3_rot(t_vec3 *v, int axis, double theta);
void			vec3_clamp(t_vec3 *v, double min, double max);
int				vec3_inverse_rotate(t_vec3 *v, t_vec3 r);
int				vec3_rotate(t_vec3 *v, t_vec3 r);
t_vec3			vec3_cross(t_vec3 va, t_vec3 vb);
t_vec3			vec3_norm(t_vec3 v);
t_vec3			vec3_reflect(t_vec3 v, t_vec3 n);
t_vec3			vec3_scale(t_vec3 va, double scale);
double			vec3_magnitude(t_vec3 v);
void			vec3_normalize(t_vec3 *v);
int				is_vec3_nul(t_vec3 v);
t_rgb			vec3_to_rgb(t_vec3 v);
t_vec3			rgb_to_vec3(t_rgb rgb);

#endif
