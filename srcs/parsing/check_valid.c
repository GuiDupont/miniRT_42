/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:27:48 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:22:49 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		check_valid_l(char **param, t_sc *sc)
{
	int result;

	result = 1;
	if (ft_array_len(param) != 4)
		result = 0;
	else
	{
		if (check_valid_pos(param[1]) != 1)
			result = 0;
		if (check_valid_luminosity(param[2]) != 1)
			result = 0;
		if (check_valid_rgb(param[3]) != 1)
			result = 0;
	}
	if (result == 0)
	{
		ft_free_split(param);
		error_and_exit("There is an issuer with your light param", 7, sc);
	}
	return (result);
}

int		check_valid_a(char **param, t_sc *sc)
{
	int result;

	result = 1;
	if (ft_array_len(param) != 3)
		result = 0;
	else
	{
		if (check_valid_luminosity(param[1]) != 1)
			result = 0;
		if (check_valid_rgb(param[2]) != 1)
			result = 0;
	}
	if (result == 0)
	{
		ft_free_split(param);
		error_and_exit("There is an issue with your ambiant light param",
		9, sc);
	}
	return (result);
}

int		check_valid_resolution(char **param, t_sc *sc)
{
	int		result;

	result = 1;
	if (ft_array_len(param) != 3)
		result = 0;
	else
	{
		if (!ft_s_isdigit(param[1]) || !ft_s_isdigit(param[2]))
			result = 0;
		if (ft_atoi(param[1]) < 0 || ft_atoi(param[2]) < 0)
			result = 0;
	}
	if (result == 0)
	{
		ft_free_split(param);
		error_and_exit("There is an issue with your resolution", 6, sc);
	}
	return (1);
}

int		check_valid_cam(char **param, t_sc *sc)
{
	int		result;

	result = 1;
	if (ft_array_len(param) != 4)
		result = 0;
	else
	{
		if (check_valid_pos(param[1]) != 1)
			result = 0;
		if (!check_valid_orientation(param[2]))
			result = 0;
		if (!check_valid_fov(param[3]))
			result = 0;
	}
	if (result == 0)
	{
		ft_free_split(param);
		error_and_exit("There is an issue with your cam parameters", 8, sc);
	}
	return (1);
}

int		check_valid_sp(char **param, t_sc *sc)
{
	int		result;

	result = 1;
	if (ft_array_len(param) != 4)
		result = 0;
	else
	{
		if (check_valid_pos(param[1]) != 1)
			result = 2;
		if (!check_valid_length(param[2]))
			result = 3;
		if (check_valid_rgb(param[3]) != 1)
			result = 4;
	}
	if (result != 1)
	{
		ft_free_split(param);
		error_and_exit("There is an issue with your sphere params", 1, sc);
	}
	return (result);
}
