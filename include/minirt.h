/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:33:41 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/19 20:00:24 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx/include/mlx.h"
# include "../minilibx/include/mlx_int.h"
# include <X11/Xlib.h>
# include <math.h>
# include "../libft/libft.h"
# include "scene.h"

/*
**	Parsing
*/

t_sc		*line_to_struct(char *line);
t_light		*init_light(void);
t_cam		*init_cam(void);
t_prim		*init_prim(char *id);
t_sc		*set_scene(void);
t_light		*set_up_l(t_sc *sc, char **param);
t_cam		*set_up_c(t_sc *sc, char **param);
int			set_up_a(t_ray *ray, char **param, t_sc *sc);
int			set_up_res(t_sc *sc, char **param);
t_prim		*set_up_sp(t_sc *sc, char **param);
t_prim		*set_up_sq(t_sc *sc, char **param);
t_prim		*set_up_pl(t_sc *sc, char **param);
t_prim		*set_up_cy(t_sc *sc, char **param);
t_prim		*set_up_tr(t_sc	*sc, char **param);
t_sc		*file_to_scene_to_image(int fd, int bmp);
void		scene_to_image(t_sc *sc, int bmp);

int			check_valid_pos(char *param);
int			check_valid_luminosity(char *param);
int			check_valid_rgb(char *param);
int			check_valid_length(char *param);
int			check_valid_fov(char *param);
int			check_valid_orientation(char *param);
int			check_valid_l(char **param, t_sc *sc);
int			check_valid_a(char **param, t_sc *sc);
int			check_valid_resolution(char **param, t_sc *sc);
int			check_valid_sp(char **param, t_sc *sc);
int			check_valid_pl(char **param, t_sc *sc);
int			check_valid_cy(char **param, t_sc *sc);
int			check_valid_sq(char **param, t_sc *sc);
int			check_valid_tr(char **param, t_sc *sc);
int			check_valid_cam(char **param, t_sc *sc);
void		check_valid_sc(t_sc *sc);

/*
**	Ray_tracing
*/

int			find_collision(t_sc *sc);
double		sp_vs_ray(t_vec *origin, t_vec *vec, t_prim *sp);
double		pl_vs_ray(t_vec *origin, t_vec *vec, t_prim *pl);
double		cy_vs_ray(t_vec *ray_o, t_vec *ray_dir, t_prim *cy);
double		ci_vs_ray(t_vec *origin, t_vec *vec, t_prim *ci);
double		tr_vs_ray(t_vec *origin, t_vec *dir, t_prim *tr);
double		sq_vs_ray(t_vec *origin, t_vec *dir, t_prim *sq);
int			ray_tracing(t_sc *sc, t_cam *cam);
void		add_prim_to_ray(t_ray *ray, t_prim *prim, double t);
int			set_up_transformation(t_sc *sc, t_cam *cam);

/*
**	Maths / Vector and Quarternions functions
*/

t_vec		cross(t_vec const *a, t_vec const *b);
t_vec		minus_v_3(t_vec a, t_vec b);
double		get_norm(t_vec *a);
t_vec		multip_vect_a(double a, t_vec const *b);
void		add_v_2(t_vec *a, t_vec *b);
t_vec		add_v_3(t_vec a, t_vec b);
void		normalize(t_vec *a);
double		get_norm2(t_vec const *a);
t_vec		gen_v_2(double x, double y, double z);
double		dot(t_vec const *a, t_vec const *b);
double		dot_2(t_vec const a, t_vec const b);

t_quat		get_rotation_quat(t_quat origin, t_quat dest);
t_quat		cross_q(t_quat const *q1, t_quat const *q2);
void		normalize_q(t_quat *a);

/*
**	Manage program
*/

void		manage_event(t_sc *sc);
void		link_for_event(t_sc *sc);
void		error_and_exit(char *str, int ref, t_sc *sc);
void		reset_ray(t_sc *sc);
void		link_image_for_each_cam(t_sc *sc);
void		transfo_p(t_sc *sc, t_prim *prim, double rt_xyz[2][3]);
void		print_transfo(t_sc *sc);
void		transfo_l(t_sc *sc, t_light *light, double rt_xyz[2][3]);
void		transfo_c(t_sc *sc, t_cam *cam, double rt_xyz[2][3]);
void		link_for_event(t_sc *sc);
void		user_transformation_ft(t_sc *sc, double rt_xyz[2][3]);
int			free_all(t_sc *sc);
void		free_light(t_sc *sc);
void		free_prim(t_sc *sc);
void		free_cam(t_sc *sc);
void		free_image_store_bmp(t_sc *sc);
void		scene_to_bmp(t_sc *sc);

#endif
