/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:13:29 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 21:02:16 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		add_line_to_struct_2(t_sc *sc, char **param)
{
	if (!(ft_strcmp(param[0], "pl")))
		set_up_pl(sc, param);
	else if (!(ft_strcmp(param[0], "sq")))
		set_up_sq(sc, param);
	else if (!(ft_strcmp(param[0], "cy")))
		set_up_cy(sc, param);
	else if (!(ft_strcmp(param[0], "tr")))
		set_up_tr(sc, param);
	else
	{
		ft_free_split(param);
		error_and_exit("One of your specs hasn't got the good id", 2, sc);
	}
	return (1);
}

int		add_line_to_struct(t_sc *sc, char *line)
{
	char	**param;

	if (line[0] == '\0')
		return (0);
	if (!(param = ft_split(line, ' ')))
		return (0);
	if (!(ft_strcmp(param[0], "l")))
		set_up_l(sc, param);
	else if (!(ft_strcmp(param[0], "A")))
		set_up_a((sc->ray), param, sc);
	else if (!(ft_strcmp(param[0], "R")))
		set_up_res(sc, param);
	else if (!(ft_strcmp(param[0], "c")))
		set_up_c(sc, param);
	else if (!(ft_strcmp(param[0], "sp")))
		set_up_sp(sc, param);
	else
		add_line_to_struct_2(sc, param);
	return (1);
}

void	set_screen_size(t_sc *sc)
{
	int x;
	int y;

	x = 0;
	y = 0;
	mlx_get_screen_size(sc->screen, &x, &y);
	if (sc->w > x)
		sc->w = x;
	if (sc->h > y)
		sc->h = y;
}

void	give_number_to_prim(t_sc *sc)
{
	int		i;
	t_prim	*prim;

	prim = sc->prim;
	i = 0;
	while (prim)
	{
		i++;
		prim->number = i;
		prim = prim->next;
	}
}

t_sc	*file_to_scene_to_image(int fd, int bmp)
{
	char	*line;
	t_sc	*sc;

	if (!(sc = set_scene()))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		add_line_to_struct(sc, line);
		free(line);
	}
	free(line);
	check_valid_sc(sc);
	if (!bmp)
	{
		sc->screen = mlx_init();
		set_screen_size(sc);
		sc->window = mlx_new_window(sc->screen, sc->w, sc->h, "RAYTRACING");
		link_image_for_each_cam(sc);
	}
	give_number_to_prim(sc);
	link_for_event(sc);
	scene_to_image(sc, bmp);
	if (!bmp)
		mlx_put_image_to_window(sc->screen, sc->window, sc->display->img, 0, 0);
	return (sc);
}
