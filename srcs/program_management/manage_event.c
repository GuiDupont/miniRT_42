/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:23:02 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 21:44:16 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	translation_rotation_2(int keycode, t_sc *sc, double rt_xyz[2][3])
{
	if (keycode == 'p' && sc->prim)
	{
		if (sc->target_p->next)
			sc->target_p = sc->target_p->next;
		else
			sc->target_p = sc->prim;
		sc->target = keycode;
	}
	else if (keycode == 'c')
		sc->target = keycode;
	else if (keycode == 65293 && !sc->light)
		user_transformation_ft(sc, rt_xyz);
}

void	translation_rotation(int keycode, t_sc *sc)
{
	static double	rt_xyz[2][3];
	static int		rotation_tranla;
	static int		xyz;

	if (keycode == 't')
		rotation_tranla = 0;
	else if (keycode == 'r')
		rotation_tranla = 1;
	else if (keycode >= 120 && keycode <= 122)
		xyz = keycode - 120;
	else if (keycode == 65362)
		rt_xyz[rotation_tranla][xyz] += 0.5;
	else if (keycode == 65364)
		rt_xyz[rotation_tranla][xyz] -= 0.5;
	else if (keycode == 'd')
		print_transfo(sc);
	else
		translation_rotation_2(keycode, sc, rt_xyz);
}

int		key_call(int keycode, t_sc *sc)
{
	if (keycode == 65307)
	{
		error_and_exit(NULL, 0, sc);
		mlx_destroy_window(sc->screen, sc->window);
	}
	else if (keycode == 110)
	{
		sc->display = sc->display->next;
		if (!sc->display)
			sc->display = sc->cam;
		mlx_put_image_to_window(sc->screen, sc->window, sc->display->img, 0, 0);
	}
	else if (keycode == 98)
	{
		sc->display = sc->cam;
		mlx_put_image_to_window(sc->screen, sc->window, sc->display->img, 0, 0);
	}
	else
		translation_rotation(keycode, sc);
	return (0);
}

int		expose_call(t_sc *sc)
{
	mlx_put_image_to_window(sc->screen, sc->window, sc->display->img, 0, 0);
	return (0);
}

void	manage_event(t_sc *sc)
{
	mlx_expose_hook(sc->window, &expose_call, sc);
	mlx_hook(sc->window, 17, 1L << 17, &free_all, sc);
	mlx_key_hook(sc->window, &key_call, sc);
	mlx_loop(sc->screen);
}
