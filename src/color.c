/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:03:03 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/07 15:56:01 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Functions to get degrade colors according to the z value
*/
/*
int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int get_color(t_point current, t_point start, t_point end, t_point delta)
{
    int     red;
    int     green;
    int     blue;
    double  percentage;

    if (current.color == end.color)
        return (current.color);
    if (delta.x > delta.y)
        percentage = percent(start.x, end.x, current.x);
    else
        percentage = percent(start.y, end.y, current.y);
    red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
    green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
    blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}
*/
/*
** Function to change the map color.
** Randomizes to any color between black(0x000000) and white(0xFFFFFF)
*/

void	ft_changecolor(t_fdf *fdf)
{
	fdf->map.color = (rand() % 0xFFFFFF);
}

/*
** Puts the initial values of the map. Call be called again to reset.
*/

void    ft_createmap(t_fdf *fdf)
{
    fdf->map.coord_x = 0;
    fdf->map.coord_y = 0;
    fdf->map.z_multiplier = 1.00;
	fdf->map.angle_x = cos(0.523599);
	fdf->map.angle_y = sin(0.523599);
	if (ceil((fdf->map.width > fdf->map.height)))
		fdf->map.scale = WIDTH / fdf->map.width;
	else
		fdf->map.scale = HEIGHT / fdf->map.height;	
	fdf->map.camera = 1;
    fdf->map.color = 0xFFFFFF;
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

int		ft_funcs(t_fdf *fdf, int key)
{
	if (key == R)
		ft_createmap(fdf);
	else if (key == W)
		fdf->map.coord_y -= 5;
	else if (key == A)
		fdf->map.coord_x += 5;
	else if (key == S)
		fdf->map.coord_y += 5;
	else if (key == D)
		fdf->map.coord_x -= 5;
	else if (key == PLUS)
		fdf->map.scale += 5;
	else if ((key == MINUS) && (fdf->map.scale > 5))
		fdf->map.scale -= 5;
	else if ((key == UP) && (fdf->map.z_multiplier < 15))
		fdf->map.z_multiplier += 0.5;
	else if ((key == DOWN) && (fdf->map.z_multiplier > -15))
		fdf->map.z_multiplier -= 0.5;
	else if (key == C)
		fdf->map.angle_y *= (fdf->map.camera++ % 2) ? 0.2 : 5;
	else if (key == X)
		ft_changecolor(fdf);
	else if (key == ESC)
		exit(0);
	return (0);
}
