/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:03:42 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/23 12:30:56 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	find_intersection_2(t_vec *origin, t_vec *vec, t_prim *prim)
{
	double	temp;

	if (prim->id == CY)
		temp = cy_vs_ray(origin, vec, prim);
	else if (prim->id == CI)
		temp = ci_vs_ray(origin, vec, prim);
	else if (prim->id == TR)
		temp = tr_vs_ray(origin, vec, prim);
	else if (prim->id == SQ)
		temp = sq_vs_ray(origin, vec, prim);
	else if (prim->id == SP)
		temp = sp_vs_ray(origin, vec, prim);
	else if (prim->id == PL)
		temp = pl_vs_ray(origin, vec, prim);
	return (temp);
}

double	find_intersection(t_vec *origin, t_vec *vec, t_sc *sc)
{
	double	temp;
	double	result;
	t_prim	*prim;

	result = __INT_MAX__;
	prim = sc->prim;
	while (prim)
	{
		temp = find_intersection_2(origin, vec, prim);
		if (temp != 0 && temp < result)
		{
			result = temp;
			sc->ray->prim = prim;
		}
		prim = prim->next;
	}
	if (result == __INT_MAX__)
		result = 0;
	return (result);
}

void	compute_light_incidence(t_light *light, t_ray *ray, t_sc *sc)
{
	double	facing_ratio;
	t_vec	light_inter;
	double	inter;
	double	intensity;
	double	distance;

	light_inter = minus_v_3(light->p, ray->inter);
	intensity = light->intensity / (get_norm(&light_inter) * G_PI);
	if (intensity > 1)
		intensity = 1;
	distance = get_norm(&light_inter);
	normalize(&light_inter);
	ray->inter = add_v_3(ray->inter, multip_vect_a(1e-4, &light_inter));
	inter = find_intersection(&(ray->inter), &light_inter, sc);
	if (inter > distance)
		inter = 0;
	inter = (inter == 0) ? 1 : 0;
	facing_ratio = fmax(0, dot(&(sc->ray->normal), &light_inter));
	ray->intensity.r += facing_ratio * (light->rgb.r * intensity) * inter;
	ray->intensity.g += facing_ratio * (light->rgb.g * intensity) * inter;
	ray->intensity.b += facing_ratio * (light->rgb.b * intensity) * inter;
}

void	compute_shading(t_sc *sc)
{
	t_light	*light;

	light = sc->light;
	while (light)
	{
		compute_light_incidence(light, sc->ray, sc);
		light = light->next;
	}
	sc->ray->intensity.r += sc->ray->ambiant.r;
	sc->ray->intensity.g += sc->ray->ambiant.g;
	sc->ray->intensity.b += sc->ray->ambiant.b;
	sc->ray->intensity.r > 1 ? sc->ray->intensity.r = 1 : 0;
	sc->ray->intensity.g > 1 ? sc->ray->intensity.g = 1 : 0;
	sc->ray->intensity.b > 1 ? sc->ray->intensity.b = 1 : 0;
	sc->ray->rgb.r *= sc->ray->intensity.r;
	sc->ray->rgb.g *= sc->ray->intensity.g;
	sc->ray->rgb.b *= sc->ray->intensity.b;
}

int		ray_tracing(t_sc *sc, t_cam *cam)
{
	double	t;
	void	*image;

	t = find_intersection(&(sc->ray->o), &(sc->ray->v), sc);
	if (t != 0)
	{
		if (t * sc->ray->v.z > sc->ray->inter.z)
			add_prim_to_ray(sc->ray, sc->ray->prim, t);
		compute_shading(sc);
	}
	image = cam->img_to_change;
	*(char*)image = sc->ray->rgb.b * 255;
	image++;
	*(char*)image = sc->ray->rgb.g * 255;
	image++;
	*(char*)image = sc->ray->rgb.r * 255;
	image++;
	*(char*)image = 0;
	image++;
	cam->img_to_change = image;
	reset_ray(sc);
	return (1);
}
