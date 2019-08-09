/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 10:47:42 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/09 11:44:36 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Gets the maximum z value * z_multiplier to use on gradient percentage.
*/
void	ft_zmax(t_fdf *fdf)
{
	int	j;
	int	i;
	int	zmax;
	int	zmin;

	j = 0;
	zmax = 0;
	zmin = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			if (fdf->values[j][i] > zmax)
				zmax = fdf->values[j][i];
			else if (fdf->values[j][i] < zmin)
				zmin = fdf->values[j][i];
			i++;
		}
		j++;
	}
	zmin *= -1;
	if (zmin > zmax)
		zmax = zmin;
	fdf->zmax = zmax * fdf->z_multiplier;
}
