/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:16 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/26 18:44:30 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1290
# define MAGNET_RADIUS 45
# define WIN_HIGHT 900
# define WALL_COLOR 0xffffff

typedef struct		s_coord
{
	int							x;
	int							y;
}									t_coord;

typedef struct		s_wall
{
	t_coord					p1;
	t_coord					p2;
	int							color;
	void						*next;
}									t_wall;

typedef struct		s_visual
{
	int							x0;
	int							y0;
	int							x1;
	int							y1;
	float						dx;
	float						dy;
	int							x0_copy;
	int							y0_copy;
	int							mem_x;
	int							mem_y;
	int							color;
}									t_visual;

typedef struct		s_core
{
	void						*mlx;
	void						*win;
	void						*image;
	void						*idata;
	int							endian;
	int							bpp;
	int							linesize;
	//
	t_wall						*wlist;
	t_visual					vs;
	int							lmb;//Left mouse button
	int							rmb;
	t_coord						last_point;
}									t_core;

void							init(t_core		*cr);
void							err_ex(int pr);
void							redraw(t_core *cr);
void							img_new(t_core *cr);
void							img_pxl(void *td, int x, int y, int color);
void							pxl_put_wrap(void *td, int x, int y, int color);
int								red_button(t_core *pr);
int								key_action(int keycode, t_core *cr);
int								mouse_press(int button, int x, int y, t_core *cr);
int								mouse_release(int button, int x, int y, t_core *cr);
int								mouse_move(int x, int y, t_core *cr);
void							bresenham(t_core *cr, void (*print_func)(void *, int, int, int));
void							add_wall(t_core *cr);
void							magnet(t_core *cr, int *x, int *y, int check_start);
float							calc_dist(int x0, int y0, int x1, int y1);

#endif