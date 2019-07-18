/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map->c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:42:27 by rquerino          #+#    #+#             */
/*   Updated: 2019/07/17 19:39:33 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

/*
** Counts how many numbers are in a row of the file.
** Returns width.
*/

int		ft_getwidth(char *line)
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
** Function that counts how many lines in the map->
** Puts the height in t_fdf.
** Returns 1 if Ok.
*/

int		ft_getheight(char *av)
{
	int		fd;
	int		h;
	char	*line;
	
	h = 0;
	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		h++;
		ft_strdel(&line);
	}
	return (h);
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
	while (split[i] && (x != fdf->map->width))
	{
		fdf->map->values[y][x] = ft_atoi(split[i]);
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
	int		x; // ->
	int		y; // \/
	int		fd;
	char	*line;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (0);
	x = 0;
	y = 0;
	fdf->map->height = ft_getheight(av);
	fdf->map->values = malloc(sizeof(int *) * (fdf->map->height));
	while (get_next_line(fd, &line) == 1)
	{
		if (y == 0)
			fdf->map->width = ft_getwidth(line);
		fdf->map->values[y] = malloc(sizeof(int) * (fdf->map->width));
		ft_getvalues(fdf, y, x, line);
		x = 0;
		y++;
		ft_strdel(&line);
	}
	return (1);
}

void	ft_freeall(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->map->height)
	{
		free(fdf->map->values[i]);
		i++;
	}
	free(fdf->map);
	free(fdf);
}