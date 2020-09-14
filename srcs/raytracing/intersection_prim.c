/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_prim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 11:44:53 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 19:15:31 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double			cy_vs_ray_2(t_vec *origin, t_vec *dir, t_solve data, t_prim *cy)
{
	float	t_new;
	t_vec	inter;
	t_prim	plan;
	t_vec	rev_v;

	t_new = __INT_MAX__;
	if (data.t1 >= 0)
		t_new = data.t1;
	else if (data.t2 >= 0)
		t_new = data.t2;
	if (t_new == __INT_MAX__)
		return (0);
	inter = add_v_3(*origin, multip_vect_a(t_new, dir));
	plan.v = cy->v;
	plan.p = cy->p;
	rev_v = multip_vect_a(-1, &(cy->v));
	if ((pl_vs_ray(&inter, &(cy->v), &plan) <= cy->height / 2.0) &&
	(pl_vs_ray(&inter, &rev_v, &plan) <= cy->height / 2.0))
		return (t_new);
	return (0);
}

double			cy_vs_ray(t_vec *origin, t_vec *dir, t_prim *cy)
{
	t_solve	data;

	normalize(&(cy->v));
	data.v_1 = cross(dir, &(cy->v));
	data.v_2 = minus_v_3(*origin, cy->p);
	data.v_3 = cross(&(data.v_2), &(cy->v));
	data.a = dot_2(data.v_1, data.v_1);
	data.b = 2 * dot_2(data.v_1, data.v_3);
	data.c = dot_2(data.v_3, data.v_3) - (pow(cy->diam / 2, 2)
	* dot_2(cy->v, cy->v));
	data.disc = (data.b * data.b) - (4 * data.a * data.c);
	if (data.disc < 0)
		return (0);
	data.t1 = (-data.b - sqrt(data.disc)) / (2 * data.a);
	data.t2 = (-data.b + sqrt(data.disc)) / (2 * data.a);
	return (cy_vs_ray_2(origin, dir, data, cy));
}

double			pl_vs_ray(t_vec *origin, t_vec *vec, t_prim *pl)
{
	double	denom;
	t_vec	polo;
	double	t;

	normalize(&(pl->v));
	denom = dot(&(pl->v), vec);
	if (denom != 0)
	{
		polo = minus_v_3(pl->p, *origin);
		t = dot(&polo, &(pl->v)) / denom;
		if (t >= 0)
			return (t);
	}
	return (0);
}

double			sp_vs_ray(t_vec *origin, t_vec *vec, t_prim *sp)
{
	double	abc[3];
	double	t[2];
	double	delta;
	t_vec	reverse_spp;

	reverse_spp = minus_v_3(*origin, sp->p);
	abc[0] = dot(vec, vec);
	abc[1] = 2 * dot(vec, &reverse_spp);
	abc[2] = dot(&reverse_spp, &reverse_spp) - pow(sp->diam * 0.5, 2);
	delta = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (delta < 0)
		return (0);
	t[0] = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	if (t[0] < 0)
		return (0);
	return (t[0]);
}

double			tr_vs_ray(t_vec *origin, t_vec *dir, t_prim *tr)
{
	t_solve		data;

	data.v_1 = minus_v_3(tr->p2, tr->p);
	data.v_2 = minus_v_3(tr->p1, tr->p);
	data.v_3 = cross(dir, &(data.v_2));
	data.disc = dot_2(data.v_1, data.v_2);
	if (ft_abs_d(data.disc) < (float)0.0000001)
		return (0);
	data.a = 1 / data.disc;
	data.v_4 = minus_v_3(*origin, tr->p);
	data.t1 = dot_2(data.v_4, data.v_3) * data.a;
	if (data.t1 < 0 || data.t1 > 1)
		return (0);
	data.v_5 = cross(&(data.v_4), &(data.v_1));
	data.t2 = dot_2(*dir, data.v_5) * data.a;
	if (data.t2 < 0 || (data.t1 + data.t2) > 1)
		return (0);
	if (dot_2(data.v_2, data.v_5) * data.a <= 0)
		return (0);
	data.t1 = dot_2(data.v_2, data.v_5) * data.a;
	if (data.t1 < 0)
		return (0);
	return (data.t1);
}
