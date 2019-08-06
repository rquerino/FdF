/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:22:13 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/06 16:44:27 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* 
cc -I minilibx_macos/ src/fdf.c src/map.c src/draw.c includes/fdf.h libft/libft.a 
-L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
*/

/*
** Allowed for mandatory: open, read, write, close, malloc, free, perror, strerror, exit,
** math library (man 3 math) and minilibx library.
** For bonus, ANY other functions if justified.
*/

static void	ft_color(t_fdf *fdf)
{
	fdf->map.color = (rand() % 0xFFFFFF);
}

void    ft_createmap(t_fdf *fdf)
{
    fdf->map.coord_x = 0; //650;
    fdf->map.coord_y = 0; //40;
    fdf->map.z_multiplier = 1.00; //For the increase/decrease on Z axis(values)
	fdf->map.angle_x = cos(0.523599); //cos(PI / 3); //0.5
	fdf->map.angle_y = sin(0.523599); //fdf->map.angle_x * sin(PI / 6); //0.5 * 0.5 = 0.25
	if (ceil((fdf->map.width > fdf->map.height)))
		fdf->map.scale = WIDTH / fdf->map.width;
	else
		fdf->map.scale = HEIGHT / fdf->map.height;	
	fdf->map.camera = 1;
    fdf->map.color = 0xFFFFFF;
}

static int	ft_funcs(int key, t_fdf *fdf)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_ANSI_R)
		ft_createmap(fdf);
	else if (key == KEY_ANSI_M)
		ft_color(fdf);
	else if (key == KEY_ANSI_W)
		fdf->map.coord_y -= 5;
	else if (key == KEY_ANSI_A)
		fdf->map.coord_x += 5;
	else if (key == KEY_ANSI_S)
		fdf->map.coord_y += 5;
	else if (key == KEY_ANSI_D)
		fdf->map.coord_x -= 5;
	else if (key == KEY_ANSI_EQUAL)
		fdf->map.scale += 5;
	else if ((key == KEY_ANSI_MINUS) && (fdf->map.scale > 5))
		fdf->map.scale -= 5;
	else if ((key == KEY_UPARROW) && (fdf->map.z_multiplier < 10))
		fdf->map.z_multiplier += 0.5;
	else if ((key == KEY_DOWNARROW) && (fdf->map.z_multiplier > -10))
		fdf->map.z_multiplier -= 0.5;
	else if (key == KEY_ANSI_C)
		fdf->map.angle_y *= (fdf->map.camera++ % 2) ? 0.2 : 5;
	return (0);
}

/*
** Handle: without parameters, too many parameters, file that doesn't exist.
** Tests: 0 x 0 map, 4x4 map, 1 value to see the difference in z axis
** Test with 42 map, random 16 x 16 map, bigger and heavier maps
*/

int     main(int ac, char **av)
{
    t_fdf *fdf;

    if (ac == 2)
    {
        fdf = malloc(sizeof(t_fdf));
        ft_readmap(fdf, av[1]);
        ft_createmap(fdf);
        fdf->mlx.init = mlx_init();
        fdf->mlx.win = mlx_new_window(fdf->mlx.init, WIDTH, HEIGHT, "FdF");
		mlx_hook(fdf->mlx.win, 2, 3, ft_keys, fdf);
        mlx_loop_hook(fdf->mlx.init, ft_drawmap, fdf);
        mlx_loop(fdf->mlx.init);
        ft_freeall(fdf);
    }
    else
        ft_putstr("Please use a single valid file.\n");
    return (0);
}


/* FDF CORRECTION

sections
preliminaries
Preliminary tests
REMEMBER THAT YOU MUST CORRECATE ONLY WHAT IS ON THE DEPOSIT OF
RENDERED BY THE STUDENT.
This is to make a "git clone" of the rendering depot, and correct what is there.
Check:
- No rendering (= nothing in the deposit git)
- No author file
- Invalid author file
- Standard (with the norminette)
- Cheats (and in particular the prohibited functions, unless justified in the context of a
bonus)
- Presence after compilation of the binary fdf
And of course, the evaluation stops if segfault or other uncontrolled error while it
could be. Attention, errors of the X server can not be diverted.

Some are due to user actions that can not be controlled (closing of
the window), others to bad programming, and that's not good. And the minilibX
native does not use the X server.
features

Error management
Test the fdf without parameter, with too many parameters, a file that does not exist or on
which you do not have rights. If the management is correct, then it's good.

Graphic
- A window appears
- Something is trace in the window
- ESC is pressed and the program is taken out of the program
- When we receive the event Expose, we retrace what is in the window

Trace
- Use a flat map with only 0, 4x4: we have a flat wire grid with a
projection that is used to give an idea of 3D
- Same map, with 1 point at a different altitude. Check that the rendering matches, and
that the impression of relief is present

Heavy
- Check the rendering of maps a little bigger: 42.fdf provided with the subject, and a map
16x16 random

From the heaviest
- Test with bigger, heavier maps. Either among those provided with the subject,
be yours. Be logical and stay compatible between what might contain your
map (more colors for example) and what the program can do to correct

Some are due to user actions that can not be controlled (closing of
the window), others to bad programming, and that's not good. And the minilibX
native does not use the X server.
features
Error management
Test the fdf without parameter, with too many parameters, a file that does not exist or on
which you do not have rights. If the management is correct, then it's good.

Graphic responsive
- If during the test preceded with heavy maps, the graph remains fluid and pleasant
it's cool

bonus
According to the bonuses present, give more or less points:
- The size of the window is determined according to the size of the map
- The size of the grid tiles changes to fit the size of the window
(- Both are possible at the same time)
- Colors, possibly according to the altitude
- Hidden Faces
- Zoom in / out (with the mouse wheel for example)
- Rotation by 90 degrees
- Fluid rotation of any angle
- Any position of the eye
- Several possible projections
- lots of other stuff
 */