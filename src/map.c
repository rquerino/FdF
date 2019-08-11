/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:42:27 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/09 19:40:53 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Counts how many numbers are in a row of the file.
** Returns width.
*/

int		ft_countnumbers(char *line)
{
	int	i;
	int	count_nbr;

	i = 0;
	count_nbr = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			count_nbr++;
			while (ft_isdigit(line[i]))
				i++;
		}
		i++;
	}
	return (count_nbr);
}

/*
** Function that counts how many lines in the map.
** Puts the height in t_fdf. Calls ft_getwidth
** Returns 1 if Ok.
*/

void	ft_getheightwidth(t_fdf *fdf, char *av)
{
	int		fd;
	int		h;
	int		w;
	char	*line;

	h = 0;
	w = 0;
	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (w == 0)
			w = ft_countnumbers(line);
		h++;
		ft_strdel(&line);
	}
	fdf->height = h;
	fdf->width = w;
}

/*
** Function that splits the line read by gnl and
** store all the values.
*/

void	ft_getvalues(t_fdf *fdf, int y, int x, char *line)
{
	int		i;
	char	**split;

	split = ft_strsplit(line, ' ');
	i = 0;
	while (split[i] && (x != fdf->width))
	{
		fdf->values[y][x] = ft_atoi(split[i]);
		i++;
		x++;
	}
	free(split);
}

/*
** Function to read map and get values. Call all other functions.
** Returns 1 if ok
*/

int		ft_readmap(t_fdf *fdf, char *av)
{
	int		x;
	int		y;
	int		fd;
	char	*line;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (0);
	x = 0;
	y = 0;
	ft_getheightwidth(fdf, av);
	fdf->values = malloc(sizeof(int *) * (fdf->height));
	while (get_next_line(fd, &line) == 1)
	{
		fdf->values[y] = malloc(sizeof(int) * (fdf->width));
		ft_getvalues(fdf, y, x, line);
		x = 0;
		y++;
		ft_strdel(&line);
	}
	return (1);
}

/*
** Frees the memory allocated in t_fdf.
*/

void	ft_freeall(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->height)
	{
		free(fdf->values[i]);
		i++;
	}
	free(fdf);
}
