/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:07:48 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/08 10:26:36 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include <libvec.h>
# include <libftprintf.h>
# include <error_ft.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>

# include <stdio.h> // TEMPORARY

# define ABS(x) (x < 0 ? -x : x)
# define MIN_POS -1000.0
# define MAX_POS 1000.0
# define EPSILON 1e-9

enum { SPHERE, CONE, PLANE, CYLINDER };
enum { POINT, SPOT, DIRECTIONAL };

typedef struct	s_arg
{
	char	*file;
	int		fd;
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

typedef struct	s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			origin;
	//t_grad			*gradient;
	int				index;
	double			fov;
	struct s_cam	*prev;
	struct s_cam	*next;
}				t_cam;

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

typedef	struct	s_lgt
{
	int				type;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			color;
	double			intensity;
	struct s_lgt	*next;
}				t_lgt;

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
	t_lgt	*lgt;
	t_ray	ray;
	t_vec3	color;
	int		recursiondepth;
}				t_env;

/*
**	main.c
*/

/*
**	parse.c
*/

void	parse(t_env *e);
void	parse_camera(t_env *e, char *str);
void	parse_lights(t_env *e, char *str);
void	parse_objects(t_env *e, char *str);
t_vec3	parse_vector(const char *line);

/*
**	create_elements.c
*/

t_cam	*create_camera(t_env *e);
t_lgt	*create_light(t_env *e);

/*
**	default.c
*/
void	default_camera(t_cam *current);
void	default_light(t_lgt *current);

/*
**	utils.c
*/

int		str_digit(char *str);
t_vec3	hex_to_vec3(const int hex);

#endif
