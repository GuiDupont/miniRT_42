/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_sp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:08:25 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_prim	*set_up_sp_2(char **param)
{
	char	**trio;
	t_prim	*sp;

	if (!(sp = init_prim(param[0])))
		return (NULL);
	if (!(trio = ft_split(param[1], ',')))
		return (NULL);
	sp->p = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	sp->diam = ft_atof(param[2]);
	if (!(trio = ft_split(param[3], ',')))
		return (NULL);
	sp->rgb.r = ft_atof(trio[0]) / 255;
	sp->rgb.g = ft_atof(trio[1]) / 255;
	sp->rgb.b = ft_atof(trio[2]) / 255;
	ft_free_split(trio);
	ft_free_split(param);
	return (sp);
}

t_prim	*set_up_sp(t_sc *sc, char **param)
{
	t_prim	*temp;

	check_valid_sp(param, sc);
	if (sc->prim == NULL)
		return (sc->prim = set_up_sp_2(param));
	temp = sc->prim;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp->next = set_up_sp_2(param));
}
