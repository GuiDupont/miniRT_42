/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:29:25 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 18:16:39 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		check_valid_pl(char **param, t_sc *sc)
{
	int result;

	result = 1;
	if (ft_array_len(param) != 4)
		result = 0;
	else
	{
		if (check_valid_pos(param[1]) != 1)
			result = 0;
		if (!check_valid_orientation(param[2]))
			result = 0;
		if (check_valid_rgb(param[3]) != 1)
			result = 0;
	}
	if (result == 0)
	{
		ft_free_split(param);
		error_and_exit("Your pl param as an issue", 2, sc);
	}
	return (1);
}

int		check_valid_tr(char **param, t_sc *sc)
{
	int result;

	result = 1;
	if (ft_array_len(param) != 5)
		result = 0;
	else
	{
		if (check_valid_pos(param[1]) != 1)
			result = 0;
		if (check_valid_pos(param[2]) != 1)
			result = 0;
		if (check_valid_pos(param[3]) != 1)
			result = 0;
	}
	if (result == 0)
	{
		ft_free_split(param);
		error_and_exit("Your tr param is wrong", 5, sc);
	}
	return (1);
}

int		check_valid_cy(char **param, t_sc *sc)
{
	int result;

	result = 1;
	if (ft_array_len(param) != 6)
		result = 0;
	else
	{
		if (!check_valid_pos(param[1]))
			result = 0;
		if (!check_valid_orientation(param[2]))
			result = 0;
		if (!check_valid_rgb(param[3]))
			result = 0;
		if (!check_valid_length(param[4]))
			result = 0;
		if (!check_valid_length(param[5]))
			result = 0;
	}
	if (result != 1)
	{
		ft_free_split(param);
		error_and_exit("Your cy param is wrong", 4, sc);
	}
	return (1);
}

int		check_valid_sq(char **param, t_sc *sc)
{
	int result;

	result = 1;
	if (ft_array_len(param) != 5)
		result = 0;
	else
	{
		if (check_valid_pos(param[1]) != 1)
			result = 0;
		if (!check_valid_orientation(param[2]))
			result = 0;
		if (!check_valid_length(param[3]))
			result = 0;
		if (!check_valid_rgb(param[4]))
			result = 0;
	}
	if (result == 0)
	{
		ft_free_split(param);
		error_and_exit("Your sq param is wrong", 3, sc);
	}
	return (1);
}
