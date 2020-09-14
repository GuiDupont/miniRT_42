/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_res_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:55:20 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		set_up_res(t_sc *sc, char **param)
{
	check_valid_resolution(param, sc);
	sc->w = ft_atoi(param[1]);
	sc->h = ft_atoi(param[2]);
	ft_free_split(param);
	return (1);
}

int		set_up_a(t_ray *ray, char **param, t_sc *sc)
{
	char	**trio;
	double	ratio;

	check_valid_a(param, sc);
	ratio = ft_atof(param[1]);
	if (!(trio = ft_split(param[2], ',')))
		return (-1);
	ray->ambiant.r = ratio * ft_atof(trio[0]) / 255;
	ray->ambiant.g = ratio * ft_atof(trio[1]) / 255;
	ray->ambiant.b = ratio * ft_atof(trio[2]) / 255;
	ft_free_split(trio);
	ft_free_split(param);
	return (1);
}
