/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 10:43:38 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	dot(t_vec const *a, t_vec const *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double	get_norm(t_vec *a)
{
	return (sqrt(dot(a, a)));
}

void	normalize(t_vec *a)
{
	double norm;

	norm = get_norm(a);
	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
}

void	add_v_2(t_vec *a, t_vec *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

t_vec	minus_v_3(t_vec dest, t_vec origin)
{
	t_vec vec;

	vec.x = dest.x - origin.x;
	vec.y = dest.y - origin.y;
	vec.z = dest.z - origin.z;
	return (vec);
}
