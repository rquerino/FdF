/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:42:27 by rquerino          #+#    #+#             */
/*   Updated: 2019/07/12 09:42:30 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Counts how many numbers are in a row of the file.
** Returns width.
*/

int	ft_getwidth(char *line)
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
** Returns the height.
*/

int	ft_getheight(t_fdf *fdf, char *av)
{
	int		fd;
	int		height;
	char	*line;
	int		count_nbr;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (0);
	height = 0;
	while (get_next_line(fd, &line) == 1)
	{
		height++;
		ft_strdel(&line);
	}
	return (height);
}

void	ft_getvalues(t_fdf *fdf, char *line)
{
	

}