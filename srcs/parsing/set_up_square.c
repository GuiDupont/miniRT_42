/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:35:23 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	set_up_sq_3(t_prim *sq)
{
	t_solve	data;

	normalize(&(sq->v));
	data.up = cross(&(sq->p), &(sq->v));
	normalize(&(data.up));
	sq->p1 = add_v_3(multip_vect_a(sq->height, &(data.up)), sq->p);
	data.right = cross(&(data.up), &(sq->v));
	normalize(&(data.right));
	sq->p2 = add_v_3(multip_vect_a(sq->height, &(data.right)), sq->p1);
	sq->p3 = add_v_3(multip_vect_a(sq->height, &(data.right)), sq->p);
}

t_prim	*set_up_sq_2(char **param)
{
	char	**trio;
	t_prim	*sq;

	if (!(sq = init_prim(param[0])))
		return (NULL);
	if (!(trio = ft_split(param[1], ',')))
		return (NULL);
	sq->p = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	if (!(trio = ft_split(param[2], ',')))
		return (NULL);
	sq->v = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	normalize(&(sq->v));
	ft_free_split(trio);
	sq->height = ft_atof(param[3]);
	if (!(trio = ft_split(param[4], ',')))
		return (NULL);
	sq->rgb.r = ft_atof(trio[0]) / 255;
	sq->rgb.g = ft_atof(trio[1]) / 255;
	sq->rgb.b = ft_atof(trio[2]) / 255;
	set_up_sq_3(sq);
	ft_free_split(trio);
	ft_free_split(param);
	return (sq);
}

t_prim	*set_up_sq(t_sc *sc, char **param)
{
	t_prim	*temp;

	check_valid_sq(param, sc);
	if (sc->prim == NULL)
		return (sc->prim = set_up_sq_2(param));
	temp = sc->prim;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp->next = set_up_sq_2(param));
}
