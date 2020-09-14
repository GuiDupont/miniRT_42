/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:17:13 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/18 17:19:38 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

# define G_PI 3.1415926535897932
# define SP 1
# define PL 2
# define SQ 3
# define CY 4
# define TR 5
# define CI 6
# define ESCAPE 65307
# define N 110
# define B 98

typedef	struct	s_rgb
{
	double	r;
	double	g;
	double	b;
}				t_rgb;

typedef	struct	s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef	struct	s_quat
{
	t_vec	v;
	double	w;
}				t_quat;

typedef struct	s_light
{
	t_vec			p;
	t_rgb			rgb;
	struct s_light	*next;
	double			intensity;
	int				number;
}				t_light;

typedef struct	s_cam
{
	t_vec			p;
	t_vec			v_original;
	void			*img;
	void			*img_to_change;
	void			*img_store;
	double			fov;
	struct s_cam	*next;
	int				x;
	int				y;
	int				number;
}				t_cam;

typedef	struct	s_prim
{
	int				id;
	int				number;
	t_vec			p;
	t_vec			p1;
	t_vec			p2;
	t_vec			p3;
	t_vec			v;
	t_rgb			rgb;
	double			height;
	double			width;
	double			diam;
	struct s_prim	*next;
}				t_prim;

typedef struct	s_ray
{
	t_vec	o;
	t_vec	v;
	t_vec	inter;
	t_prim	*prim;
	t_rgb	rgb;
	t_vec	normal;
	double	facing_ratio;
	t_rgb	ambiant;
	t_rgb	intensity;
}				t_ray;

typedef struct	s_sc
{
	t_light	*light;
	t_cam	*cam;
	t_prim	*prim;
	t_prim	*target_p;
	t_light	*target_l;
	t_ray	*ray;
	t_vec	origin;
	t_vec	cam_dir;
	t_cam	*display;
	int		h;
	int		w;
	void	*screen;
	void	*window;
	int		target;
}				t_sc;

typedef struct	s_solve
{
	t_vec	edge0;
	t_vec	edge1;
	t_vec	edge2;
	t_vec	edge3;
	t_vec	v_1;
	t_vec	v_2;
	t_vec	v_3;
	t_vec	v_4;
	t_vec	v_5;
	double	disc;
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	t_vec	up;
	t_vec	right;
}				t_solve;

#endif
