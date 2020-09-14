/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 12:02:59 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 13:16:00 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	free_image_store_bmp(t_sc *sc)
{
	t_cam *cam;

	if (!sc->cam)
		return ;
	cam = sc->cam;
	while (cam)
	{
		free(cam->img_store);
		cam = cam->next;
	}
}

void	free_cam(t_sc *sc)
{
	t_cam *cam;
	t_cam *next;

	if (!sc->cam)
		return ;
	cam = sc->cam;
	while (cam->next)
	{
		next = cam->next;
		if (cam->img)
			mlx_destroy_image(sc->screen, cam->img);
		free(cam);
		cam = next;
	}
	if (cam->img)
		mlx_destroy_image(sc->screen, cam->img);
	free(cam);
	sc->cam = NULL;
}

void	free_prim(t_sc *sc)
{
	t_prim *prim;
	t_prim *previous;

	prim = sc->prim;
	while (sc->prim)
	{
		previous = NULL;
		while (prim->next)
		{
			previous = prim;
			prim = prim->next;
		}
		free(prim);
		if (previous)
			previous->next = NULL;
		else
			sc->prim = NULL;
		prim = sc->prim;
	}
}

void	free_light(t_sc *sc)
{
	t_light *light;
	t_light *previous;

	light = sc->light;
	while (sc->light)
	{
		previous = NULL;
		while (light->next)
		{
			previous = light;
			light = light->next;
		}
		free(light);
		if (previous)
			previous->next = NULL;
		else
			sc->light = NULL;
		light = sc->light;
	}
}
