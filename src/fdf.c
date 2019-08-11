/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:22:13 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/10 14:35:49 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Print structions
*/

void	ft_instructions(void)
{
	ft_putstr("WASD:		Move map\n");
	ft_putstr("+ / -:		Zoom (Increase/Decrease map scale)\n");
	ft_putstr("UP / DOWN:	Increase/Decrease depth (Z Axis)\n");
	ft_putstr("C:		Change camera\n");
	ft_putstr("X:		Randomize color of base and gradient\n");
	ft_putstr("Z:		Remove gradient\n");
	ft_putstr("R:		Reset the map to initial configuration\n");
	ft_putstr("ESC:		Exit\n");
}

/*
** Functions to get gradient colors according to the z value
** and between colorbase and colorgradient.
*/

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		ft_getcolor(t_fdf *fdf, double z)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (z < 0)
		z *= -1;
	else if (z == 0)
		return (fdf->colorbase);
	else if (z >= 300)
		return (fdf->colorgradient);
	percentage = z / 300;
	red = get_light((fdf->colorbase >> 16) & 0xFF,
			(fdf->colorgradient >> 16) & 0xFF, percentage);
	green = get_light((fdf->colorbase >> 8) & 0xFF,
			(fdf->colorgradient >> 8) & 0xFF, percentage);
	blue = get_light(fdf->colorbase & 0xFF,
			fdf->colorgradient & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

/*
** Allowed for mandatory: open, read, write, close, malloc,
** free, perror, strerror, exit, math library (man 3 math) and
** minilibx library.
** For bonus, ANY other functions if justified.
** Handle: without parameters, too many parameters, file that doesn't exist.
** Tests: 0 x 0 map, 4x4 map, 1 value to see the difference in z axis
** Test with 42 map, random 16 x 16 map, bigger and heavier maps
** mlx_hook: 2 is for handling key pressing on x_event,
** 0 is for x_maks - doesn't work on mac
*/

int		main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac == 2)
	{
		ft_instructions();
		fdf = malloc(sizeof(t_fdf));
		ft_readmap(fdf, av[1]);
		ft_createmap(fdf);
		fdf->mlx = mlx_init();
		fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
		mlx_hook(fdf->win, 2, 0, ft_funcs, fdf);
		mlx_loop_hook(fdf->mlx, ft_drawmap, fdf);
		mlx_loop(fdf->mlx);
		ft_freeall(fdf);
	}
	else
		ft_putstr("Please use one single valid file.\n");
	return (0);
}
