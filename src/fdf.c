/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:22:13 by rquerino          #+#    #+#             */
/*   Updated: 2019/07/19 09:54:02 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** To compile : cc -I minilibx_macos/ src/fdf.c src/map.c src/fdf.h libft/libft.a 
** -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
*/

/*
** Allowed for mandatory: open, read, write, close, malloc, free, perror, strerror, exit,
** math library (man 3 math) and minilibx library.
** For bonus, ANY other functions if justified.
*/

void    ft_keys()
{
    ft_putstr("key pressed\n");
}

void    ft_originalmap(t_fdf *fdf)
{
    fdf->color.R = 0;
    fdf->color.G = 255;
    fdf->color.B = 0;
}


void    ft_printvalues(t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 11)
    {
        while (j < 18)
        {
            printf("%02d ,", fdf->map.values[i][j]);
            j++;
        }
        j = 0;
        i++;
        printf("\n");
    }
}

int     main(int ac, char **av)
{
    t_fdf *fdf;

    if (ac == 2)
    {
        fdf = malloc(sizeof(t_fdf));
        ft_readmap(fdf, av[1]);
        ft_printvalues(fdf);
        printf("width: %d, height: %d\n", fdf->map.width, fdf->map.height);
        fdf->mlx.init = mlx_init();
        fdf->mlx.win = mlx_new_window(fdf->mlx.init, WIDTH, HEIGHT, "FdF");
        mlx_loop(fdf->mlx.init);
        mlx_hook(fdf->mlx.win, 2, 3, ft_keys, fdf);
        ft_freeall(fdf);
    }
    else
        ft_putstr("Please use a valid file.\n");
    return (0);
}