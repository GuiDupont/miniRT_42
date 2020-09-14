/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:47:07 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/23 12:26:46 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static	void	compute_sp_normal(t_ray *ray, t_prim *sp)
{
	ray->normal = minus_v_3(ray->inter, sp->p);
	normalize(&(ray->normal));
}

static	void	compute_cy_normal(t_ray *ray, t_prim *cy)
{
	double	t;
	t_prim	pl;
	t_vec	cy_v_rev;

	pl.v = cy->v;
	pl.p = cy->p;
	t = pl_vs_ray(&(ray->inter), &(cy->v), &pl);
	if (t != 0)
	{
		ray->normal = minus_v_3(ray->inter,
		add_v_3(cy->p, multip_vect_a(-t, &(cy->v))));
	}
	cy_v_rev = multip_vect_a(-1, &(cy->v));
	t = pl_vs_ray(&(ray->inter), &cy_v_rev, &pl);
	if (t != 0)
	{
		ray->normal = minus_v_3(ray->inter,
		add_v_3(cy->p, multip_vect_a(t, &(cy->v))));
	}
	normalize(&(ray->normal));
}

void			add_prim_to_ray(t_ray *ray, t_prim *prim, double t)
{
	ray->prim = prim;
	ray->inter.z = t * ray->v.z + ray->o.z;
	ray->inter.y = t * ray->v.y + ray->o.y;
	ray->inter.x = t * ray->v.x + ray->o.x;
	ray->rgb.r = prim->rgb.r;
	ray->rgb.g = prim->rgb.g;
	ray->rgb.b = prim->rgb.b;
	if (prim->id == SP)
		compute_sp_normal(ray, prim);
	if (prim->id == PL || prim->id == CI || prim->id == TR || prim->id == SQ)
		ray->normal = prim->v;
	if (prim->id == CY)
		compute_cy_normal(ray, prim);
}

void			reset_ray(t_sc *sc)
{
	sc->ray->rgb.r = 0;
	sc->ray->rgb.g = 0;
	sc->ray->rgb.b = 0;
	sc->ray->inter = (t_vec) {0.0, 0.0, -__INT_MAX__};
	sc->ray->prim = NULL;
	sc->ray->intensity.r = 0;
	sc->ray->intensity.g = 0;
	sc->ray->intensity.b = 0;
}
