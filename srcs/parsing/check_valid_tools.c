/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:30:53 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 18:05:14 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		check_valid_orientation(char *param)
{
	int		i;
	char	**xyz;

	i = 0;
	while (param[i])
	{
		if (!ft_isdigit(param[i]) && param[i] != ',' && param[i] != '.'
		&& param[i] != '-')
			return (0);
		i++;
	}
	xyz = ft_split(param, ',');
	if (ft_array_len(xyz) != 3 || ft_atof(xyz[0]) > 1 || ft_atof(xyz[0]) < -1 ||
		ft_atof(xyz[1]) > 1 || ft_atof(xyz[1]) < -1 || ft_atof(xyz[2]) > 1 ||
		ft_atof(xyz[2]) < -1 || (ft_atof(xyz[0]) == 0 && ft_atof(xyz[1]) == 0 &&
		ft_atof(xyz[2]) == 0))
	{
		ft_free_split(xyz);
		return (0);
	}
	ft_free_split(xyz);
	return (1);
}

int		check_valid_fov(char *param)
{
	if (!ft_s_isdigit(param))
		return (0);
	if (ft_atoi(param) < 0 || ft_atoi(param) > 180)
		return (0);
	return (1);
}

int		check_valid_length(char *param)
{
	int i;

	i = 0;
	while (param[i])
	{
		if (!ft_isdigit(param[i]) && param[i] != '.')
			return (0);
		i++;
	}
	if (ft_atoi(param) < 0)
		return (0);
	return (1);
}

int		check_valid_pos(char *param)
{
	int		i;
	char	**xyz;

	i = 0;
	while (param[i])
	{
		if (!(ft_isdigit(param[i])) && param[i] != ',' &&
		param[i] != '.' && param[i] != '-' && param[i] != '+')
			return (0);
		i++;
	}
	xyz = ft_split(param, ',');
	if (ft_array_len(xyz) != 3)
	{
		ft_free_split(xyz);
		return (0);
	}
	ft_free_split(xyz);
	return (1);
}

int		check_valid_luminosity(char *param)
{
	int		i;
	double	luminosity;

	i = 0;
	if (!param)
		return (0);
	while (param[i])
	{
		if (!(ft_isdigit(param[i])) && param[i] != '.')
			return (0);
		i++;
	}
	luminosity = ft_atof(param);
	if (luminosity > 1 || luminosity < 0)
		return (0);
	return (1);
}
