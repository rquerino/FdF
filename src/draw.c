/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 22:42:23 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/07 14:50:07 by rquerino         ###   ########.fr       */
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


void    ft_bresenham(t_fdf *fdf)
{
	double x;
	double y;
	double dx;
	double dy;
	double unitvector;

	x = fdf->map.x0;
	y = fdf->map.y0;
	dx = fdf->map.x1 - fdf->map.x0;
	dy = fdf->map.y1 - fdf->map.y0;
	unitvector = sqrt((pow(dx, 2)) + (pow(dy, 2)));
	dx /= unitvector;
	dy /= unitvector;
	while (unitvector > 0)
	{
        mlx_pixel_put(fdf->mlx.init, fdf->mlx.win, x, y, fdf->map.color);
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

    xt = x - fdf->map.width / 2;
    yt = y - fdf->map.height / 2;
    fdf->map.x0 = (fdf->map.angle_x * (xt - yt) * fdf->map.scale) +
        (WIDTH / 2) + fdf->map.coord_x;
    fdf->map.x1 = (fdf->map.angle_x * (xt - (yt + 1)) * fdf->map.scale) +
        (WIDTH / 2) + fdf->map.coord_x;
    fdf->map.y0 = (fdf->map.angle_y * (xt + yt) * fdf->map.scale) -
        (fdf->map.values[y][x] * fdf->map.z_multiplier) +
        (HEIGHT / 2) + fdf->map.coord_y;
    fdf->map.y1 = (fdf->map.angle_y * (xt + (yt + 1)) * fdf->map.scale) -
        (fdf->map.values[y + 1][x] * fdf->map.z_multiplier) +
        (HEIGHT / 2) + fdf->map.coord_y;
    ft_bresenham(fdf);
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

    xt = x - fdf->map.width / 2;
    yt = y - fdf->map.height / 2;
    fdf->map.x0 = (fdf->map.angle_x * (xt - yt) * fdf->map.scale) +
        (WIDTH / 2) + fdf->map.coord_x;
    fdf->map.x1 = (fdf->map.angle_x * ((xt + 1) - yt) * fdf->map.scale) +
        (WIDTH / 2) + fdf->map.coord_x;
    fdf->map.y0 = (fdf->map.angle_y * (xt + yt) * fdf->map.scale) -
        (fdf->map.values[y][x] * fdf->map.z_multiplier) +
        (HEIGHT / 2) + fdf->map.coord_y;
    fdf->map.y1 = (fdf->map.angle_y * ((xt + 1) + yt) * fdf->map.scale) -
        (fdf->map.values[y][x + 1] * fdf->map.z_multiplier) +
        (HEIGHT / 2) + fdf->map.coord_y;
    ft_bresenham(fdf);
}

int     ft_drawmap(t_fdf *fdf)
{
    int y;
    int x;

    y = 0;
    mlx_clear_window(fdf->mlx.init, fdf->mlx.win);
    while (y < fdf->map.height)
    {
        x = 0;
        while (x < fdf->map.width)
        {
            fdf->map.x0 = x;
            fdf->map.y0 = y;
            if (fdf->map.width > x + 1)
                ft_horizontalline(fdf, y, x);
            if (fdf->map.height > y + 1)
                ft_verticalline(fdf, y, x);
            x++;
        }
        y++;
    }
    return (0);
}


/*

void    ft_bresenham(t_fdf *fdf)
{
    int dx;
    int dy;
    int p;
    //int x;
    //int y;
 
	dx = fdf->map.x1 - fdf->map.x0;
	dy = fdf->map.y1 - fdf->map.y0;
	//x = fdf->map.x0;
	//y = fdf->map.y0;
	p = 2 * dy - dx;
	while(fdf->map.x0 < fdf->map.x1)
	{
		if(p >= 0)
		{
            mlx_pixel_put(fdf->mlx.init, fdf->mlx.win, fdf->map.x0, fdf->map.y0, fdf->map.color);
			fdf->map.y0 += 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			mlx_pixel_put(fdf->mlx.init, fdf->mlx.win, fdf->map.x0, fdf->map.y0, fdf->map.color);
			p = p + 2 * dy;
		}
		fdf->map.x0 += 1;
	}
}
*/
/*
** Multiplies Z axis(values[y][x]) * z_multiplier (increase/decrease depth)
** Also multiplies by the scale
** returns the y coordinate (still without angles)
*/
/*
int     ft_coordy(t_fdf *fdf, int y, int x, int z)
{
    z *= fdf->map.z_multiplier;
    if (z > fdf->map.zmax)
        z = fdf->map.zmax;
    if (z < fdf->map.zmin)
        z = fdf->map.zmin;
    //return (fdf->map.coord_y + ((fdf->map.scale * x) + (fdf->map.scale * y) - (z * 2)));

    return ((fdf->map.xangle * ((x - fdf->map.width / 2) + (y - fdf->map.height / 2))
        * fdf->map.scale) - (fdf->map.values[y][x] * fdf->map.z_multiplier)
        + (HEIGHT / 2) + fdf->map.coord_y);
}

int     ft_coordx(t_fdf *fdf, int y, int x)
{
    //return (fdf->map.coord_x - (fdf->map.scale * y) + (fdf->map.scale * x));
    return ((fdf->map.xangle * ((x - fdf->map.width / 2) - (y - fdf->map.height / 2))
        * fdf->map.scale) + ((WIDTH / 2) + fdf->map.coord_x));
}
*/
/*
int     ft_coordy(t_fdf *fdf, int y, int x, int z)
{
    z *= fdf->map.z_multiplier;
    if (z > fdf->map.zmax)
        z = fdf->map.zmax;
    if (z < fdf->map.zmin)
        z = fdf->map.zmin;
    return ((-z * fdf->map.scale + (x * fdf->map.scale + y * fdf->map.scale) 
        * fdf->map.yangle) + fdf->map.coord_y);
}

int     ft_coordx(t_fdf *fdf, int y, int x)
{
    return (((x * fdf->map.scale - y * fdf->map.scale) * fdf->map.xangle) + fdf->map.coord_x);
}
*/
/*
void    ft_drawvertical(t_fdf *fdf)
{
    int y;
    int x;

    y = 0;
    while (y < fdf->map.height)
    {
        x = 0;
        while (x < fdf->map.width - 1)
        {
            fdf->map.x0 = ft_coordx(fdf, y, x);
            fdf->map.y0 = ft_coordy(fdf, y, x, fdf->map.values[y][x]);
            fdf->map.x1 = ft_coordx(fdf, y, x + 1);
            fdf->map.y1 = ft_coordy(fdf, y, x + 1, fdf->map.values[y][x + 1]);
            ft_bresenham(fdf);
            x++;
        }
        y++;
    }    
}

void    ft_drawhorizontal(t_fdf *fdf)
{
    int y;
    int x;

    y = 0;
    while (y < fdf->map.height - 1)
    {
        x = 0;
        while (x < fdf->map.width)
        {
            fdf->map.x0 = ft_coordx(fdf, y, x);
            fdf->map.y0 = ft_coordy(fdf, y, x, fdf->map.values[y][x]);
            fdf->map.x1 = ft_coordx(fdf, y + 1, x);
            fdf->map.y1 = ft_coordy(fdf, y + 1, x, fdf->map.values[y + 1][x]);
            ft_bresenham(fdf);
            x++;
        }
        y++;
    }
}
*/
/*
** Function to draw the map.
int    ft_drawmap(t_fdf *fdf)
{
    mlx_clear_window(fdf->mlx.init, fdf->mlx.win);
    ft_drawhorizontal(fdf);
    ft_drawvertical(fdf);
    return (0);
}
*/
