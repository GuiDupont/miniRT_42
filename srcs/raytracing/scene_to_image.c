/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:25:01 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 21:03:29 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	link_image_for_each_cam(t_sc *sc)
{
	t_cam	*cam;
	void	*tmp;
	int		bytes_p_pixel;
	int		size_line;
	int		endian;

	bytes_p_pixel = 4;
	size_line = bytes_p_pixel * sc->w;
	if (*(char *)&endian == 1)
		endian = 0;
	else
		endian = 1;
	cam = sc->cam;
	while (cam != NULL)
	{
		cam->img = mlx_new_image(sc->screen, sc->w, sc->h);
		tmp = mlx_get_data_addr(cam->img, &bytes_p_pixel, &size_line, &endian);
		cam->img_store = tmp;
		cam = cam->next;
	}
}

void	generate_image(t_sc *sc, t_cam *cam)
{
	double	xyz[3];

	set_up_transformation(sc, cam);
	cam->y = 0;
	while (cam->y < sc->h)
	{
		cam->x = 0;
		while (cam->x < sc->w)
		{
			xyz[0] = cam->x - sc->w / 2;
			xyz[1] = cam->y - sc->h / 2;
			xyz[2] = -sc->w / 2 / tan(cam->fov / 2);
			sc->ray->v = (t_vec) {xyz[0], -xyz[1], xyz[2]};
			normalize(&(sc->ray->v));
			ray_tracing(sc, cam);
			cam->x += 1;
		}
		cam->y += 1;
	}
}

void	scene_to_image(t_sc *sc, int bmp)
{
	t_cam	*cam;

	cam = sc->cam;
	while (cam != NULL)
	{
		if (bmp)
		{
			if (!(cam->img_store = malloc(sizeof(void*) * sc->h * sc->w * 4)))
				error_and_exit("Issue while creating bmp file", 12, sc);
		}
		cam->img_to_change = cam->img_store;
		generate_image(sc, cam);
		cam = cam->next;
	}
}
