/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_to_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:38:22 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 18:51:40 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	set_header_bmp(int padding_size, t_sc *sc, int fd)
{
	unsigned char	*file_header;
	int				file_size;

	if (!(file_header = ft_calloc(14, sizeof(unsigned char))))
		return ;
	file_size = 40 + 14 + (4 * sc->w + padding_size) * sc->h;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(40 + 14);
	write(fd, file_header, 14);
	ft_strdel((char**)&file_header);
}

void	bitmap_info_header(t_sc *sc, int fd)
{
	unsigned char	*info_header;

	if (!(info_header = ft_calloc(40, sizeof(unsigned char))))
		return ;
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(sc->w);
	info_header[5] = (unsigned char)(sc->w >> 8);
	info_header[6] = (unsigned char)(sc->w >> 16);
	info_header[7] = (unsigned char)(sc->w >> 24);
	info_header[8] = (unsigned char)(sc->h);
	info_header[9] = (unsigned char)(sc->h >> 8);
	info_header[10] = (unsigned char)(sc->h >> 16);
	info_header[11] = (unsigned char)(sc->h >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(32);
	write(fd, info_header, 40);
	ft_strdel((char**)&info_header);
}

void	scene_to_bmp(t_sc *sc)
{
	int				fd;
	int				i;
	int				padding_size;
	unsigned char	padding[3];

	ft_bzero(padding, 3);
	if ((fd = open("image_saved.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644))
	<= 0)
		return ;
	ft_bzero(padding, 3);
	padding_size = (4 - (sc->w * 4) % 4) % 4;
	i = sc->h;
	set_header_bmp(padding_size, sc, fd);
	bitmap_info_header(sc, fd);
	while (i >= 0)
	{
		write(fd, sc->display->img_store + (i * sc->w * 4), 4 * sc->w);
		write(fd, &padding[0], padding_size);
		i--;
	}
	close(fd);
}
