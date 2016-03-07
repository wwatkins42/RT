/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:47:28 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/07 11:54:05 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include <libvec.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>

# define ABS(x) (x < 0 ? -x : x)
# define MIN_POS -1000.0
# define MAX_POS 1000.0
# define EPSILON 1e-9

enum { SPHERE, CONE, PLANE, CYLINDER };

typedef struct	s_arg
{
	char	*file_scene;
	int		w;
	int		h;
}				t_arg;

typedef struct	s_img
{
	void	*adr;
	char	*img;
	int		endian;
	int		bpp;
	int		opp;
	int		sl;
}				t_img;

typedef struct	s_mat
{
	t_vec3	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
	double	reflex;
	double	refract;
}				t_mat;

typedef struct	s_obj
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			normal;
	t_mat			mat;
	short			type;
	double			scale;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			origin;
	double			fov;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_ray
{
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		hit;
}				t_ray;

typedef struct	s_win
{
	void	*adr;
	int		w;
	int		h;
	int		dw;
	int		dh;
}				t_win;

typedef struct	s_env
{
	void	*mlx;
	t_win	win;
	t_arg	arg;
	t_img	img;
	t_cam	*cam;
	t_obj	*obj;
	t_ray	ray;
	t_vec3	color;
	int		recursiondepth;
}				t_env;

/*
**	main.c functions
*/


#endif
