/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:21:46 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_cam	*set_up_c_2(char **param, int number)
{
	char	**trio;
	t_cam	*c;

	c = init_cam();
	c->number = number;
	if (!(trio = ft_split(param[1], ',')))
		return (NULL);
	c->p.x = ft_atof(trio[0]);
	c->p.y = ft_atof(trio[1]);
	c->p.z = ft_atof(trio[2]);
	ft_free_split(trio);
	if (!(trio = ft_split(param[2], ',')))
		return (NULL);
	c->v_original = (t_vec) {ft_atof(trio[0]), ft_atof(trio[1]),
	ft_atof(trio[2])};
	ft_free_split(trio);
	c->fov = ft_atof(param[3]) / 180 * G_PI;
	ft_free_split(param);
	c->img = NULL;
	c->img_store = NULL;
	c->next = NULL;
	return (c);
}

t_cam	*set_up_c(t_sc *sc, char **param)
{
	t_cam		*temp;
	static int	number;

	check_valid_cam(param, sc);
	if (sc->cam == NULL)
		return (sc->cam = set_up_c_2(param, ++number));
	temp = sc->cam;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp->next = set_up_c_2(param, ++number));
}
