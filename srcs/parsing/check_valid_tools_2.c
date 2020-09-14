/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tools_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:32:28 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		check_valid_rgb(char *param)
{
	int		i;
	char	**rgb;

	i = 0;
	while (param[i])
	{
		if (!ft_isdigit(param[i]) && param[i] != ',')
			return (0);
		i++;
	}
	rgb = ft_split(param, ',');
	if (ft_array_len(rgb) != 3)
	{
		ft_free_split(rgb);
		return (0);
	}
	if (ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) > 255
		|| ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[2]) < 0)
	{
		ft_free_split(rgb);
		return (0);
	}
	ft_free_split(rgb);
	return (1);
}
