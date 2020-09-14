/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_event_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:23:55 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 22:52:44 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	print_transfo(t_sc *sc)
{
	char *str;

	str = "Transformation to apply to the ";
	if (sc->target == 'p')
		ft_printf("\n%sprimitive %d\n", str, sc->target_p->number);
	else if (sc->target == 'c')
		ft_printf("\n%scurrent cam", str);
}

void	adjust_rotation(t_vec *direction, t_vec *save_up)
{
	if (direction->x > 1 || direction->x < -1)
		direction->x /= direction->x;
	if (direction->y > 1 || direction->y < -1)
		direction->y /= direction->y;
	if (direction->z > 1 || direction->z < -1)
		direction->z /= direction->z;
	if (direction->x == 0 && direction->y == 0 && direction->z == 0)
		*(direction) = *(save_up);
}

void	transfo_p(t_sc *sc, t_prim *prim, double rt_xyz[2][3])
{
	t_vec	rotation;
	t_vec	translation;
	t_vec	save_up;

	translation = (t_vec) {rt_xyz[0][0], rt_xyz[0][1], rt_xyz[0][2]};
	if (prim->id != CI && prim->id != CY)
		add_v_2(&(prim->p), &translation);
	if (prim->id == TR)
	{
		add_v_2(&(prim->p2), &translation);
		add_v_2(&(prim->p3), &translation);
	}
	save_up = prim->v;
	if (prim->id == PL || prim->id == SQ)
	{
		rotation = (t_vec) {rt_xyz[1][0], rt_xyz[1][1], rt_xyz[1][2]};
		add_v_2(&(prim->v), &rotation);
		adjust_rotation(&(prim->v), &save_up);
	}
	scene_to_image(sc, 0);
}

void	transfo_l(t_sc *sc, t_light *light, double rt_xyz[2][3])
{
	t_vec	translation;

	translation = (t_vec) {rt_xyz[0][0], rt_xyz[0][1], rt_xyz[0][2]};
	add_v_2(&(light->p), &translation);
	scene_to_image(sc, 0);
}

void	transfo_c(t_sc *sc, t_cam *cam, double rt_xyz[2][3])
{
	t_vec	rotation;
	t_vec	translation;
	t_vec	save_up;

	translation = (t_vec) {rt_xyz[0][0], rt_xyz[0][1], rt_xyz[0][2]};
	add_v_2(&(cam->p), &translation);
	save_up = cam->v_original;
	rotation = (t_vec) {rt_xyz[1][0], rt_xyz[1][1], rt_xyz[1][2]};
	add_v_2(&(cam->v_original), &rotation);
	adjust_rotation(&(cam->v_original), &save_up);
	scene_to_image(sc, 0);
}
