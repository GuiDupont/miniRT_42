/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:43:56 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_light	*set_up_l_2(char **param, int number)
{
	char	**trio;
	t_light	*l;

	l = init_light();
	l->number = number;
	if (!(trio = ft_split(param[1], ',')))
		return (NULL);
	l->p = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]), ft_atof(trio[2])};
	ft_free_split(trio);
	l->intensity = ft_atof(param[2]) * 50;
	if (!(trio = ft_split(param[3], ',')))
		return (NULL);
	l->rgb.r = ft_atof(trio[0]) / 255;
	l->rgb.g = ft_atof(trio[1]) / 255;
	l->rgb.b = ft_atof(trio[2]) / 255;
	ft_free_split(trio);
	ft_free_split(param);
	return (l);
}

t_light	*set_up_l(t_sc *sc, char **param)
{
	t_light		*temp;
	static int	number;

	check_valid_l(param, sc);
	if (sc->light == NULL)
		return (sc->light = set_up_l_2(param, ++number));
	temp = sc->light;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp->next = set_up_l_2(param, ++number));
}
