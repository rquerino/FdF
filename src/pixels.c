/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 22:42:23 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/09 11:44:12 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** This will be the start of my own perspective of bresenham algorithm
** 
*/
/*
void    ft_bresenham(t_fdf *fdf)
{
    int dy;
    int dx;
    int f;

    dy = fdf->map.y1 - fdf->map.y0;
    dx = fdf->map.x1 - fdf->map.x0;
    f = (dx > dy ? dx : dy) / 2;
    mlx_pixel_put(fdf->mlx.init, fdf->mlx.win, fdf->map.x0, fdf->map.y0, fdf->map.color);
    while (fdf->map.x0 < fdf->map.x1 || fdf->map.y0 < fdf->map.y1)
    {
        if (f < 0)
            f = f + (dx > dy ? dx : dy) - (dx < dy ? dx : dy);
        else
            f -= (dx < dy ? dx : dy);
        if (f > 0)
        {
            if (dx > dy)
                fdf->map.x0 += 1;
            else
                fdf->map.y0 += 1;
        }
        else
        {
            fdf->map.x0 += 1;
            fdf->map.y0 += 1; 
        }
        mlx_pixel_put(fdf->mlx.init, fdf->mlx.win, fdf->map.x0, fdf->map.y0, fdf->map.color);
    }
}*/

int		ft_gradienter(t_fdf *fdf, int z0, int z1, int uv)
{
	int zstart;
	int zend;

	zstart = z0 * fdf->z_multiplier;
	zend = z1 * fdf->z_multiplier;
	return ((zend - zstart) / (uv % 1));
}

void    ft_bresenham(t_fdf *fdf, int x0, int x1, int y0, int y1)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	unitvector;
	int		gradienter;
	int		z;

	x = fdf->x0;
	y = fdf->y0;
	dx = fdf->x1 - fdf->x0;
	dy = fdf->y1 - fdf->y0;
	unitvector = sqrt((pow(dx, 2)) + (pow(dy, 2)));
	dx /= unitvector;
	dy /= unitvector;
	gradienter = ft_gradienter(fdf, fdf->values[y0][x0], fdf->values[y1][x1], unitvector);
	z = 0;
	while (unitvector > 0)
	{
		fdf->color = ft_getcolor(fdf, z += gradienter);
        mlx_pixel_put(fdf->mlx, fdf->win, x, y, fdf->color);
		x += dx;
		y += dy;
		unitvector -= 1;
	}
}

/*
** Function to draw lines in y axis.
** The formula for the x axis is:
**
** The formula for the y axis is:
**
*/

void    ft_verticalline(t_fdf *fdf, int y, int x)
{
    int xt;
    int yt;

    xt = x - fdf->width / 2;
    yt = y - fdf->height / 2;
    fdf->x0 = (fdf->angle_x * (xt - yt) * fdf->scale) +
        (WIDTH / 2) + fdf->coord_x;
    fdf->x1 = (fdf->angle_x * (xt - (yt + 1)) * fdf->scale) +
        (WIDTH / 2) + fdf->coord_x;
    fdf->y0 = (fdf->angle_y * (xt + yt) * fdf->scale) -
        (fdf->values[y][x] * fdf->z_multiplier) +
        (HEIGHT / 2) + fdf->coord_y;
    fdf->y1 = (fdf->angle_y * (xt + (yt + 1)) * fdf->scale) -
        (fdf->values[y + 1][x] * fdf->z_multiplier) +
        (HEIGHT / 2) + fdf->coord_y;
    ft_bresenham(fdf, x, x, y, y + 1);
}

/*
** Function to draw lines in x axis.
** The formula for the x axis is:
**
** The formula for the y axis is:
**
*/

void    ft_horizontalline(t_fdf *fdf, int y, int x)
{
    int xt;
    int yt;

    xt = x - fdf->width / 2;
    yt = y - fdf->height / 2;
    fdf->x0 = (fdf->angle_x * (xt - yt) * fdf->scale) +
        (WIDTH / 2) + fdf->coord_x;
    fdf->x1 = (fdf->angle_x * ((xt + 1) - yt) * fdf->scale) +
        (WIDTH / 2) + fdf->coord_x;
    fdf->y0 = (fdf->angle_y * (xt + yt) * fdf->scale) -
        (fdf->values[y][x] * fdf->z_multiplier) +
        (HEIGHT / 2) + fdf->coord_y;
    fdf->y1 = (fdf->angle_y * ((xt + 1) + yt) * fdf->scale) -
        (fdf->values[y][x + 1] * fdf->z_multiplier) +
        (HEIGHT / 2) + fdf->coord_y;
    ft_bresenham(fdf, x, x + 1, y, y);
}

int     ft_drawmap(t_fdf *fdf)
{
    int y;
    int x;

    y = 0;
    mlx_clear_window(fdf->mlx, fdf->win);
	ft_zmax(fdf);
    while (y < fdf->height)
    {
        x = 0;
        while (x < fdf->width)
        {
            fdf->x0 = x;
            fdf->y0 = y;
            if (fdf->width > x + 1)
                ft_horizontalline(fdf, y, x);
            if (fdf->height > y + 1)
                ft_verticalline(fdf, y, x);
            x++;
        }
        y++;
    }
    return (0);
}
