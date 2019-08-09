/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:25:36 by rquerino          #+#    #+#             */
/*   Updated: 2019/08/08 20:50:02 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FILLIT_H
# include <mlx.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

# define WIDTH		1366
# define HEIGHT		768
# define W			13
# define A			0
# define S			1
# define D			2
# define R			15
# define C			8
# define X			7
# define PLUS		24
# define MINUS		27
# define UP			126
# define DOWN		125
# define ESC		53

/*
** Structures
*/

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		coord_x;
	int		coord_y;
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		scale;
	int		camera;
	double	z_multiplier;
	double	angle_x;
	double	angle_y;
	int		zmax;
	int		**values;
	int		color;
	int		colorbase;
	int		colorgradient;
}				t_fdf;

/*
** Functions
*/

int		ft_countnumbers(char *line);
void	ft_getheightwidth(t_fdf *fdf, char *av);
void	ft_getvalues(t_fdf *fdf, int y, int x, char *line);
int		ft_readmap(t_fdf *fdf, char *av);
void	ft_freeall(t_fdf *fdf);
void	ft_bresenham(t_fdf *fdf, int x0, int x1, int y0, int y1);
int		ft_drawmap(t_fdf *fdf);
void	ft_horizontalline(t_fdf *fdf, int y, int x);
void	ft_verticalline(t_fdf *fdf, int y, int x);
void	ft_createmap(t_fdf *fdf);
int		ft_coordx(t_fdf *fdf, int y, int x);
int     ft_coordy(t_fdf *fdf, int y, int x, int z);
void	ft_changecolor(t_fdf *fdf);
int		ft_funcs(int key, t_fdf *fdf);
void	ft_changeangle(t_fdf *fdf);
int		ft_getcolor(t_fdf *fdf, int z);

#endif
