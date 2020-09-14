/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:59:08 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 17:56:08 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		free_all(t_sc *sc)
{
	if (sc)
	{
		free_cam(sc);
		free_prim(sc);
		free_light(sc);
		free(sc->ray);
	}
	if (sc->screen && sc->window)
	{
		mlx_clear_window(sc->screen, sc->window);
		mlx_destroy_window(sc->screen, sc->window);
	}
	free(sc);
	exit(0);
	return (0);
}

void	error_and_exit(char *str, int ref, t_sc *sc)
{
	if (ref)
		ft_printf("error %d : %s\n", ref, str);
	if (sc)
		free_all(sc);
	exit(0);
}
