/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:03:03 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/10 14:34:27 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Function to change the map color.
** Randomizes to any color between black(0x000000) and white(0xFFFFFF)
*/

void	ft_changecolor(int key, t_fdf *fdf)
{
	if (key == Z)
		fdf->colorgradient = fdf->colorbase;
	else
	{
		fdf->colorbase = (rand() % 0xFFFFFF);
		fdf->colorgradient = (rand() % 0xFFFFFF);
	}
}

/*
** Puts the initial values of the map. Call be called again to reset.
*/

void	ft_createmap(t_fdf *fdf)
{
	fdf->coord_x = 0;
	fdf->coord_y = 0;
	fdf->z_multiplier = 1.00;
	fdf->angle_x = cos(0.523599);
	fdf->angle_y = sin(0.523599);
	if (fdf->width > fdf->height)
		fdf->scale = WIDTH / fdf->width * 0.5;
	else
		fdf->scale = HEIGHT / fdf->height * 0.5;
	fdf->camera = 1;
	fdf->colorbase = 0x213D58;
	fdf->color = 0x213D58;
	fdf->colorgradient = 0xFF00B4;
}

/*
** Changes between the 3 angles of view.
** 1 is isometric, 2 is parallel, 3 is from above.
*/

void	ft_changeangle(t_fdf *fdf)
{
	if (fdf->camera == 1)
	{
		fdf->camera = 2;
		fdf->angle_y = sin(0.523599) * 0.2;
	}
	else if (fdf->camera == 2)
	{
		fdf->camera = 3;
		fdf->angle_x = cos(M_PI / 9);
		fdf->angle_y = sin(M_PI / 9);
	}
	else if (fdf->camera == 4)
	{
		fdf->camera = 1;
		fdf->angle_x = cos(0.523599);
		fdf->angle_y = sin(0.523599);
	}
	else if (fdf->camera == 3)
	{
		fdf->camera = 4;
		fdf->angle_x = 1;
		fdf->angle_y = 1;
	}
}

/*
** R: Reset initial configs
** WASD: Move figure
** +/-: Zoom (increase/decrease map scale)
** up/down arrow: Increase/decrease depth (z axis)
** C: Change camera (iso/frontal)
** X: Change color
** ESC: Exit
*/

int		ft_funcs(int key, t_fdf *fdf)
{
	if (key == R)
		ft_createmap(fdf);
	else if (key == W)
		fdf->coord_y -= 5;
	else if (key == D)
		fdf->coord_x += 5;
	else if (key == S)
		fdf->coord_y += 5;
	else if (key == A)
		fdf->coord_x -= 5;
	else if (key == PLUS)
		fdf->scale += 5;
	else if ((key == MINUS) && (fdf->scale > 5))
		fdf->scale -= 5;
	else if ((key == UP) && (fdf->z_multiplier < 12))
		fdf->z_multiplier += 1;
	else if ((key == DOWN) && (fdf->z_multiplier > -12))
		fdf->z_multiplier -= 1;
	else if (key == C)
		ft_changeangle(fdf);
	else if (key == X || key == Z)
		ft_changecolor(key, fdf);
	else if (key == ESC)
		exit(0);
	return (1);
}
