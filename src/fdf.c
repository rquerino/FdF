/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:22:13 by rquerino          #+#    #+#             */
/*   Updated: 2019/07/17 18:56:13 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>
/*
** To compile : cc -I minilibx_macos/ src/fdf.c src/map.c src/fdf.h libft/libft.a 
** -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
*/

/*
** Allowed for mandatory: open, read, write, close, malloc, free, perror, strerror, exit,
** math library (man 3 math) and minilibx library.
** For bonus, ANY other functions if justified.
*/

/*
void    ft_minilibx(void *mlx_ptr, t_point size)
{
    int px;
    int py;

    px = 0;
    py = 0;
    void *win_ptr;
    win_ptr = mlx_new_window(mlx_ptr, size.x * 2, size.y * 2, "map");
    while (px++ <= size.x && py++ <= size.y)
        mlx_pixel_put(mlx_ptr, 10 + win_ptr, 10 + px, 10 + py, 0xFFFFFF);


}
*/
void    ft_printvalues(t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (fdf->map.values[i])
    {
        while (fdf->map.values[i][j])
        {
            printf("%d ", fdf->map.values[i][j]);
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
        fdf = malloc(sizeof(fdf));
        ft_readmap(fdf, av[1]);
        ft_printvalues(fdf);

    }
    else
        ft_putstr("Please use a valid file.\n");
    return (0);
}