/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:25:36 by rquerino          #+#    #+#             */
/*   Updated: 2019/07/18 21:53:35 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FILLIT_H
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

# define WIDTH		(1366)
# define HEIGHT		(768)

typedef struct	s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}		t_mlx;

typedef struct	s_color
{
	int	R;
	int	G;
	int	B;
}		t_color;

typedef struct	s_map
{
	int	width;
	int	height;
	int	z_max;
	int	z_min;
	int	**values;
}				t_map;

typedef struct	s_fdf
{
	t_mlx	mlx;
	t_map	map;
	t_color	color;
}				t_fdf;


/*
** Functions
*/

int		ft_countnumbers(char *line);
void	ft_getheightwidth(t_fdf *fdf, char *av);
void	ft_getvalues(t_fdf *fdf, int y, int x, char *line);
int		ft_readmap(t_fdf *fdf, char *av);
void	ft_freeall(t_fdf *fdf);

#endif
