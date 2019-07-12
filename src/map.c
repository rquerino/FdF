/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:42:27 by rquerino          #+#    #+#             */
/*   Updated: 2019/07/12 09:42:30 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Reads the map and stores all values
*/

char     **ft_readmap(int fd)
{
    int i;
    int j;
    int k;
    char *buff;
    char **values;
    char *str;

    i = 0;
    while (get_next_line(fd, &buff) > 0)
    {
        ft_strcat(ft_strcat(str, buff), "\n");
        ft_strdel(&buff);
    }
    values = ft_strsplit(str, ' ');
    ft_strdel(&str);
    return (values);
}

/*
** Checks the map size. Not sure if it's really needed.
*/

t_point     ft_mapsize(char **values)
{
    t_point size;
    int i;
    int j;

    i = 0;
    size.x = ft_strlen(values[0]);
    size.y = 0;
    while (values[i])
        i++;
    size.y = i;
    return (size);
}
