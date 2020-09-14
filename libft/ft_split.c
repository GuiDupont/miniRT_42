/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:13:47 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/02 16:48:33 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		size(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static int		size_dest(char const *str, char c)
{
	int	i;
	int	y;

	i = 0;
	y = 1;
	while (str[i])
	{
		if (str[i] != c)
		{
			i = i + size(&str[i], c);
			y++;
		}
		i++;
	}
	return (y);
}

static	char	**free_all_n_quit(char **to_free, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	return (NULL);
}

char			**ft_split(char const *str, char c)
{
	char	**final;
	int		i;
	int		y;

	if (!str)
		return (NULL);
	if (!(final = malloc(sizeof(*final) * size_dest(str, c))))
		return (NULL);
	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (!(final[y] = ft_substr(&str[i], 0, size(&str[i], c))))
				return (free_all_n_quit(final, y));
			i = i + size(&str[i], c);
			y++;
		}
		if (str[i])
			i++;
	}
	final[y] = NULL;
	return (final);
}
