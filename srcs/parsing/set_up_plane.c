/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:26:19 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_prim	*set_up_pl_2(char **param)
{
	char	**trio;
	t_prim	*pl;
	double	div;

	if (!(pl = init_prim(param[0])))
		return (NULL);
	if (!(trio = ft_split(param[1], ',')))
		return (NULL);
	pl->p = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	if (!(trio = ft_split(param[2], ',')))
		return (NULL);
	pl->v = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	if (!(trio = ft_split(param[3], ',')))
		return (NULL);
	div = 1.0 / 255;
	pl->rgb.r = ft_atof(trio[0]) * div;
	pl->rgb.g = ft_atof(trio[1]) * div;
	pl->rgb.b = ft_atof(trio[2]) * div;
	ft_free_split(trio);
	ft_free_split(param);
	return (pl);
}

t_prim	*set_up_pl(t_sc *sc, char **param)
{
	t_prim	*temp;

	check_valid_pl(param, sc);
	if (sc->prim == NULL)
		return (sc->prim = set_up_pl_2(param));
	temp = sc->prim;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp->next = set_up_pl_2(param));
}
