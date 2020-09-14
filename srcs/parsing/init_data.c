/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:02:15 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_light		*init_light(void)
{
	t_light *light;

	if (!(light = malloc(sizeof(t_light))))
		return (0);
	light->p = (t_vec) {0.0, 0.0, 0.0};
	light->rgb = (t_rgb) {0.0, 0.0, 0.0};
	light->next = NULL;
	return (light);
}

t_cam		*init_cam(void)
{
	t_cam *cam;

	if (!(cam = malloc(sizeof(t_cam))))
		return (0);
	cam->p = (t_vec) {0.0, 0.0, 0.0};
	cam->v_original = (t_vec) {0.0, 0.0, 0.0};
	cam->fov = 0.0;
	cam->img = NULL;
	cam->next = NULL;
	return (cam);
}

t_prim		*init_prim(char *id)
{
	t_prim	*prim;

	if (!(prim = malloc(sizeof(t_prim))))
		return (0);
	if (!(ft_strcmp(id, "sp")))
		prim->id = SP;
	if (!(ft_strcmp(id, "pl")))
		prim->id = PL;
	if (!(ft_strcmp(id, "sq")))
		prim->id = SQ;
	if (!(ft_strcmp(id, "tr")))
		prim->id = TR;
	if (!(ft_strcmp(id, "cy")))
		prim->id = CY;
	if (!(ft_strcmp(id, "ci")))
		prim->id = CI;
	prim->next = NULL;
	return (prim);
}

t_ray		*set_ray(void)
{
	t_ray *ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (0);
	ray->o = (t_vec) {0.0, 0.0, 0.0};
	ray->inter = (t_vec) {0.0, 0.0, -__INT_MAX__};
	ray->prim = NULL;
	ray->rgb = (t_rgb) {0, 0, 0};
	ray->ambiant = ((t_rgb) {0, 0, 0});
	ray->intensity = ((t_rgb) {0, 0, 0});
	return (ray);
}

t_sc		*set_scene(void)
{
	t_sc	*sc;

	if (!(sc = malloc(sizeof(t_sc))))
		return (NULL);
	sc->light = NULL;
	sc->cam = NULL;
	sc->prim = NULL;
	sc->ray = set_ray();
	sc->window = NULL;
	sc->screen = NULL;
	sc->w = 0;
	sc->h = 0;
	sc->origin = (t_vec) {0.0, 0.0, 0.0};
	sc->cam_dir = (t_vec) {0.0, 0.0, -1.0};
	return (sc);
}
