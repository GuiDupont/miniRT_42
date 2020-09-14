/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_cy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:54:45 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	add_ci_to_cy(t_prim *cy)
{
	t_prim *circle_1;
	t_prim *circle_2;

	if (!(circle_1 = init_prim("ci")))
		return ;
	if (!(circle_2 = init_prim("ci")))
		return ;
	normalize(&(cy->v));
	circle_1->p = add_v_3(cy->p, multip_vect_a(-(cy->height) / 2, &(cy->v)));
	circle_1->v = multip_vect_a(-1, &(cy->v));
	circle_1->rgb = cy->rgb;
	circle_1->diam = cy->diam;
	circle_2->v = cy->v;
	circle_2->rgb = cy->rgb;
	circle_2->diam = cy->diam;
	circle_2->p = add_v_3(cy->p, multip_vect_a(cy->height / 2, &(cy->v)));
	cy->next = circle_1;
	circle_1->next = circle_2;
}

t_prim	*set_up_cy_2(char **param)
{
	char	**trio;
	t_prim	*cy;

	if (!(cy = init_prim(param[0])))
		return (NULL);
	if (!(trio = ft_split(param[1], ',')))
		return (NULL);
	cy->p = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	if (!(trio = ft_split(param[2], ',')))
		return (NULL);
	cy->v = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	if (!(trio = ft_split(param[3], ',')))
		return (NULL);
	cy->rgb.r = ft_atof(trio[0]) / 255;
	cy->rgb.g = ft_atof(trio[1]) / 255;
	cy->rgb.b = ft_atof(trio[2]) / 255;
	ft_free_split(trio);
	cy->diam = ft_atof(param[4]);
	cy->height = ft_atof(param[5]);
	add_ci_to_cy(cy);
	ft_free_split(param);
	return (cy);
}

t_prim	*set_up_cy(t_sc *sc, char **param)
{
	t_prim	*temp;

	check_valid_cy(param, sc);
	if (sc->prim == NULL)
		return (sc->prim = set_up_cy_2(param));
	temp = sc->prim;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp->next = set_up_cy_2(param));
}
