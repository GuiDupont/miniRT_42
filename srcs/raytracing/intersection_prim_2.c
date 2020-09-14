/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_prim_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 11:51:47 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double			sq_vs_ray(t_vec *origin, t_vec *dir, t_prim *sq)
{
	t_solve	data;

	data.b = dot(dir, &(sq->v));
	if (data.b == 0)
		return (0);
	data.a = dot_2(minus_v_3(*origin, sq->p), sq->v);
	if ((data.a < 0 && data.b < 0) || (data.a > 0 && data.b > 0))
		return (0);
	data.t1 = -data.a / data.b;
	if (data.t1 < 0)
		return (0);
	data.v_1 = minus_v_3(add_v_3(multip_vect_a(data.t1, dir), *origin), sq->p);
	data.t2 = sq->height / 2;
	if (ft_abs_d(data.v_1.x) > data.t2 || ft_abs_d(data.v_1.y) > data.t2
	|| ft_abs_d(data.v_1.z) > data.t2)
		return (0);
	return (data.t1);
}

double			ci_vs_ray(t_vec *origin, t_vec *vec, t_prim *ci)
{
	double	t;
	double	distance2;
	double	radius2;
	t_vec	d;

	t = pl_vs_ray(origin, vec, ci);
	if (!t)
		return (0);
	d = minus_v_3(add_v_3(multip_vect_a(t, vec), *origin), ci->p);
	radius2 = (ci->diam / 2) * (ci->diam / 2);
	distance2 = dot(&d, &d);
	if (distance2 <= radius2)
		return (t);
	return (0);
}
