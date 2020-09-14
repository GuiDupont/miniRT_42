/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_prim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:34:04 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/23 13:07:18 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void		transform_vec(t_quat *rota, t_vec *vec)
{
	t_quat	rota_conj;
	t_quat	result;

	rota_conj = *rota;
	rota_conj.v = multip_vect_a(-1, &(rota_conj.v));
	result.v = *vec;
	result = cross_q(rota, &result);
	result = cross_q(&result, &rota_conj);
	*vec = result.v;
}

void		transform_prim(t_sc *sc, t_quat *rota, t_vec *transla)
{
	t_prim	*prim;

	prim = sc->prim;
	while (prim != NULL)
	{
		add_v_2(&(prim->p), transla);
		transform_vec(rota, &(prim->p));
		if (prim->id == TR || prim->id == SQ)
		{
			add_v_2(&(prim->p1), transla);
			transform_vec(rota, &(prim->p1));
			add_v_2(&(prim->p2), transla);
			transform_vec(rota, &(prim->p2));
			add_v_2(&(prim->p3), transla);
			transform_vec(rota, &(prim->p3));
		}
		else if (prim->id == PL || prim->id == CY || prim->id == CI ||
		prim->id == SQ || prim->id == TR)
		{
			transform_vec(rota, &(prim->v));
			normalize(&(prim->v));
		}
		prim = prim->next;
	}
}

void		transform_scene(t_sc *sc, t_quat *rota, t_vec *transla)
{
	t_cam	*cam;
	t_light	*light;

	cam = sc->cam;
	while (cam != NULL)
	{
		add_v_2(&(cam->p), transla);
		transform_vec(rota, &(cam->p));
		transform_vec(rota, &(cam->v_original));
		normalize(&(cam->v_original));
		cam = cam->next;
	}
	light = sc->light;
	while (light != NULL)
	{
		add_v_2(&(light->p), transla);
		transform_vec(rota, &(light->p));
		light = light->next;
	}
	transform_prim(sc, rota, transla);
}

void		adjust_cylinder(t_prim *prim)
{
	while (prim)
	{
		if (prim->id == CY && prim->p.x == 0 && prim->p.y == 0 &&
		prim->v.x == 0 && (prim->v.y == 1 || prim->v.y == -1)
		&& prim->v.z == 0)
		{
			prim->p.y += 0.000001;
			prim->next->p.y += 0.000001;
			prim->next->next->p.y += 0.000001;
		}
		prim = prim->next;
	}
}

int			set_up_transformation(t_sc *sc, t_cam *cam)
{
	t_vec		translation;
	t_quat		rota;

	rota.v = cam->v_original;
	rota.w = 0;
	if (!rota.v.x && !rota.v.y && rota.v.z == -1)
		rota = (t_quat) {(t_vec) {0.0, 0.0, 0.0}, 1.0};
	else if (!rota.v.x && !rota.v.y && rota.v.z == 1)
		rota = (t_quat) {(t_vec) {0.0, 1.0, 0.0}, 0.0};
	else
		rota = get_rotation_quat(rota,
		(t_quat) {(t_vec) {0.0, 0.0, -1.0}, 0.0});
	transform_vec(&rota, &(cam->v_original));
	normalize(&(cam->v_original));
	translation = minus_v_3(sc->origin, cam->p);
	transform_scene(sc, &rota, &translation);
	adjust_cylinder(sc->prim);
	return (1);
}
