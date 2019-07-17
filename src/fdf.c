/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:22:13 by rquerino          #+#    #+#             */
/*   Updated: 2019/07/12 09:22:52 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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

void    ft_printmap(int **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            printf("%d ", map[i][j]);
            j++;
        }
        j = 0;
        i++;
        printf("\n");
    }
}

int     main(int argc, char **argv)
{
    //void *mlx_ptr;
    int fd;
    int **map;
    //t_point size;

    if (argc == 2)
    {
        map = NULL;
        /*
        if (fd != -1)
        {
            fd = open(argv[1], O_RDONLY);
            map = ft_readmap(fd);
            //size = malloc(sizeof(size));
            size = ft_mapsize(values);
            ft_printvalues(values);
            mlx_ptr = mlx_init();
            ft_minilibx(mlx_ptr, values, size);
        } */
        fd = open(argv[1], O_RDONLY);
        map = ft_readmap(fd, map);
        ft_printmap(map);
    }
    else
        ft_putstr("Please use a valid file.\n");
    
    return (0);
}