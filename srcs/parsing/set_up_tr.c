/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_tr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:59:59 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_prim	*set_up_tr_3(t_prim *tr, char **param)
{
	char		**trio;

	if (!(trio = ft_split(param[4], ',')))
		return (NULL);
	tr->rgb.r = ft_atof(trio[0]) / 255;
	tr->rgb.g = ft_atof(trio[1]) / 255;
	tr->rgb.b = ft_atof(trio[2]) / 255;
	ft_free_split(trio);
	ft_free_split(param);
	return (tr);
}

t_prim	*set_up_tr_2(char **param)
{
	char	**trio;
	t_prim	*tr;

	if (!(tr = init_prim(param[0])))
		return (NULL);
	if (!(trio = ft_split(param[1], ',')))
		return (NULL);
	tr->p = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	if (!(trio = ft_split(param[2], ',')))
		return (NULL);
	tr->p1 = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	if (!(trio = ft_split(param[3], ',')))
		return (NULL);
	tr->p2 = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	return (set_up_tr_3(tr, param));
}

t_prim	*set_up_tr(t_sc *sc, char **param)
{
	t_prim	*temp;

	check_valid_tr(param, sc);
	if (sc->prim == NULL)
		return (sc->prim = set_up_tr_2(param));
	temp = sc->prim;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp->next = set_up_tr_2(param));
}
