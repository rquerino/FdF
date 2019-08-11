/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 22:42:23 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/10 13:53:27 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Function to draw the line.
** p is the amount of points to connect x0,y0 to x1,y1.
** p is square of (dx^2)+(xy^2).
** dx dy: is the difference between x0 and x1, and y0 and y1.
** dx and dy will be divided by the number of points.
** the values will be added to x and y until x1,y1 is reached.
** double to int rounds down (ex: 1.89 will be 1)
*/

void	ft_bresenham(t_fdf *fdf, int z0, int z1, double gradienter)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	points;

	x = fdf->x0;
	y = fdf->y0;
	dx = fdf->x1 - fdf->x0;
	dy = fdf->y1 - fdf->y0;
	points = sqrt((pow(dx, 2)) + (pow(dy, 2)));
	dx /= points;
	dy /= points;
	gradienter = z0 * fdf->z_multiplier;
	while (points > 0)
	{
		fdf->color = ft_getcolor(fdf, gradienter);
		mlx_pixel_put(fdf->mlx, fdf->win, x, y, fdf->color);
		x += dx;
		y += dy;
		gradienter += ((z1 - z0) * fdf->z_multiplier) / points;
		points -= 1;
	}
}

/*
** Functions to draw lines in y(vertical) axis
** and x(horizontal) axis. (3D to 2D transformation)
** The formula for the x axis is:
** (angle x scale x (xpos - ypos)) + (screen size/2) + initial pos (0)
** The formula for the y axis is:
** (angle x scale x (xpos + ypos)) + (screen size/2) + initial pos - Z
** The differences are the sum/subtraction of xpos and ypos, and
** Z axis value is subtracted from y.
*/

void	ft_yaxis(t_fdf *fdf, int y, int x)
{
	int		xpos;
	int		ypos;
	double	gradienter;

	gradienter = 0.0;
	xpos = x - fdf->width / 2;
	ypos = y - fdf->height / 2;
	fdf->x0 = (fdf->angle_x * (xpos - ypos) * fdf->scale) +
		(WIDTH / 2) + fdf->coord_x;
	fdf->x1 = (fdf->angle_x * (xpos - ypos - 1) * fdf->scale) +
		(WIDTH / 2) + fdf->coord_x;
	fdf->y0 = (fdf->angle_y * (xpos + ypos) * fdf->scale) -
		(fdf->values[y][x] * fdf->z_multiplier) +
		(HEIGHT / 2) + fdf->coord_y;
	fdf->y1 = (fdf->angle_y * (xpos + ypos + 1) * fdf->scale) -
		(fdf->values[y + 1][x] * fdf->z_multiplier) +
		(HEIGHT / 2) + fdf->coord_y;
	ft_bresenham(fdf, fdf->values[y][x], fdf->values[y + 1][x], gradienter);
}

void	ft_xaxis(t_fdf *fdf, int y, int x)
{
	int		xpos;
	int		ypos;
	double	gradienter;

	gradienter = 0.0;
	xpos = x - fdf->width / 2;
	ypos = y - fdf->height / 2;
	fdf->x0 = (fdf->angle_x * (xpos - ypos) * fdf->scale) +
		(WIDTH / 2) + fdf->coord_x;
	fdf->x1 = (fdf->angle_x * (xpos + 1 - ypos) * fdf->scale) +
		(WIDTH / 2) + fdf->coord_x;
	fdf->y0 = (fdf->angle_y * (xpos + ypos) * fdf->scale) -
		(fdf->values[y][x] * fdf->z_multiplier) +
		(HEIGHT / 2) + fdf->coord_y;
	fdf->y1 = (fdf->angle_y * (xpos + 1 + ypos) * fdf->scale) -
		(fdf->values[y][x + 1] * fdf->z_multiplier) +
		(HEIGHT / 2) + fdf->coord_y;
	ft_bresenham(fdf, fdf->values[y][x], fdf->values[y][x + 1], gradienter);
}

/*
** Initial function to start drawing the map.
** Draws lines horizontally and vertically based on width and height.
*/

int		ft_drawmap(t_fdf *fdf)
{
	int y;
	int x;

	y = 0;
	mlx_clear_window(fdf->mlx, fdf->win);
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			fdf->x0 = x;
			fdf->y0 = y;
			if (fdf->width > x + 1)
				ft_xaxis(fdf, y, x);
			if (fdf->height > y + 1)
				ft_yaxis(fdf, y, x);
			x++;
		}
		y++;
	}
	return (0);
}
