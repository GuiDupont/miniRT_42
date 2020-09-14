/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 12:19:30 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_quat	cross_q(t_quat const *q1, t_quat const *q2)
{
	double	w;
	double	dx;
	double	dy;
	double	dz;
	t_quat	result;

	w = q1->w * q2->w - q1->v.x * q2->v.x - q1->v.y
	* q2->v.y - q1->v.z * q2->v.z;
	dx = q1->w * q2->v.x + q1->v.x * q2->w + q1->v.y
	* q2->v.z - q1->v.z * q2->v.y;
	dy = q1->w * q2->v.y - q1->v.x * q2->v.z + q1->v.y
	* q2->w + q1->v.z * q2->v.x;
	dz = q1->w * q2->v.z + q1->v.x * q2->v.y - q1->v.y
	* q2->v.x + q1->v.z * q2->w;
	result.v = (t_vec) {dx, dy, dz};
	result.w = w;
	return (result);
}

double	dot_q(t_quat *q1, t_quat *q2)
{
	return (q1->v.x * q2->v.x + q1->v.y * q2->v.y +
	q1->v.z * q2->v.z + q1->w * q2->w);
}

double	get_norm_q(t_quat *a)
{
	return (sqrt(dot_q(a, a)));
}

void	normalize_q(t_quat *a)
{
	double norm;

	norm = 1.0 / get_norm_q(a);
	a->w *= norm;
	a->v.x *= norm;
	a->v.y *= norm;
	a->v.z *= norm;
}

t_quat	get_rotation_quat(t_quat origin, t_quat dest)
{
	t_vec		v;
	t_quat		quat;
	double		sinus;
	double		angle;

	normalize_q(&origin);
	normalize_q(&dest);
	v = cross(&(origin.v), &(dest.v));
	normalize(&v);
	angle = acos(dot_q(&origin, &dest)) * 0.5;
	sinus = sin(angle);
	quat = (t_quat) {(t_vec) {v.x * sinus, v.y * sinus, v.z * sinus},
	cos(angle)};
	normalize_q(&quat);
	return (quat);
}
