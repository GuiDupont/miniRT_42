/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_event_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 12:06:50 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 21:14:40 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	link_for_event(t_sc *sc)
{
	sc->target_p = sc->prim;
	sc->display = sc->cam;
}

void	user_transformation_ft(t_sc *sc, double rt_xyz[2][3])
{
	if (sc->target == 'p')
		transfo_p(sc, sc->target_p, rt_xyz);
	else if (sc->target == 'c')
		transfo_c(sc, sc->display, rt_xyz);
	mlx_put_image_to_window(sc->screen, sc->window, sc->display->img, 0, 0);
}
