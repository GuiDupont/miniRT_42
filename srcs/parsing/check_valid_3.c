/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 12:18:56 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 18:18:04 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	check_valid_sc(t_sc *sc)
{
	if (!sc->h || !sc->w)
		error_and_exit("There is an issue with your resolution", 6, sc);
	if (!sc->cam)
		error_and_exit("There is no camera", 8, sc);
}
