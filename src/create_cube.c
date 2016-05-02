/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:34:43 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 19:26:29 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		aux(t_obj *cube, double k)
{
	cube->comp[4].pos = cube->comp[0].pos;
	cube->comp[4].pos2 = (t_vec3) {k, 0, 0};
	cube->comp[4].pos3 = (t_vec3) {0, 0, k};
	cube->comp[4].dir = vec3(0, -1, 0);
	cube->comp[5].pos = vec3_add(cube->comp[0].pos, (t_vec3) {k, 0, k});
	cube->comp[5].pos2 = (t_vec3) {-k, 0, 0};
	cube->comp[5].pos3 = (t_vec3) {0, k, 0};
	cube->comp[5].dir = vec3(0, 0, 1);
}

void			create_cube(t_env *e, t_obj *cube)
{
	double	k;

	!(cube->comp = malloc(6 * sizeof(t_obj))) ? error(e, E_MALLOC, NULL, 0) : 0;
	k = cube->scale;
	cube->comp[0].pos = vec3_sub(cube->pos, vec3(k / 2, k / 2, k / 2));
	cube->comp[0].pos2 = (t_vec3) {k, 0, 0};
	cube->comp[0].pos3 = (t_vec3) {0, k, 0};
	cube->comp[0].dir = vec3(0, 0, -1);
	cube->comp[1].pos = vec3_add(cube->comp[0].pos, (t_vec3) {k, 0, 0});
	cube->comp[1].pos2 = (t_vec3) {0, 0, k};
	cube->comp[1].pos3 = (t_vec3) {0, k, 0};
	cube->comp[1].dir = vec3(1, 0, 0);
	cube->comp[2].pos = vec3_add(cube->comp[0].pos, (t_vec3) {0, 0, k});
	cube->comp[2].pos2 = (t_vec3) {0, 0, -k};
	cube->comp[2].pos3 = (t_vec3) {0, k, 0};
	cube->comp[2].dir = vec3(-1, 0, 0);
	cube->comp[3].pos = vec3_add(cube->comp[0].pos, (t_vec3) {0, k, 0});
	cube->comp[3].pos2 = (t_vec3) {k, 0, 0};
	cube->comp[3].pos3 = (t_vec3) {0, 0, k};
	cube->comp[3].dir = vec3(0, 1, 0);
	aux(cube, k);
}
