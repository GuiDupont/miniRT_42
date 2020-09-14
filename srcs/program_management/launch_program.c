/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:21:53 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 13:12:52 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_sc	*launch_raytracing(int fd, int bmp)
{
	t_sc	*sc;

	sc = file_to_scene_to_image(fd, bmp);
	if (bmp)
	{
		scene_to_bmp(sc);
		free_image_store_bmp(sc);
		free_all(sc);
	}
	else
		manage_event(sc);
	return (sc);
}

int		check_rt_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (len <= 3)
		return (0);
	if (file_name[len - 3] == '.' &&
		(file_name[len - 2] == 'r' || file_name[len - 2] == 'R') &&
		(file_name[len - 1] == 't' || file_name[len - 1] == 'T'))
		return (1);
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;

	if (ac < 2 || ac > 3)
		error_and_exit("You forgot to give a RT file", 10, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Error in the opening of the file", 10, NULL);
	if (!check_rt_file(av[1]))
		error_and_exit("This is not a RT file", 10, NULL);
	if (ac == 3 && ft_strcmp(av[2], "-save"))
		error_and_exit("There is a mistake in your second argument", 11, NULL);
	if (ac == 3)
		launch_raytracing(fd, 1);
	else
		launch_raytracing(fd, 0);
	return (0);
}
