/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:00:00 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec	multip_vect_a(double a, t_vec const *b)
{
	t_vec	vec;

	vec.x = a * b->x;
	vec.y = a * b->y;
	vec.z = a * b->z;
	return (vec);
}

t_vec	add_v_3(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

double	dot_2(t_vec const a, t_vec const b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	cross(t_vec const *a, t_vec const *b)
{
	double dx;
	double dy;
	double dz;

	dx = a->y * b->z - a->z * b->y;
	dy = a->z * b->x - a->x * b->z;
	dz = a->x * b->y - a->y * b->x;
	return (gen_v_2(dx, dy, dz));
}

t_vec	gen_v_2(double x, double y, double z)
{
	t_vec vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}
