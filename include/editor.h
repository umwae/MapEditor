/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:16 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/31 19:19:52 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1290
# define WIN_HIGHT 900

# define MAGNET_RADIUS 30
# define SELECT_RADIUS 60
# define SELECT_PADDING 30

# define WALL_COLOR 0xECF7FF
# define SELECT_COLOR 0xFFD200
# define MENU_COLOR 0xA0A0A0

# define PI_CEIL 4

# define INST_PANEL_X 0
# define INST_PANEL_Y WIN_HIGHT / 5

typedef struct		s_coord
{
	int							x;
	int							y;
}									t_coord;

typedef struct		s_wall
{
	t_coord					p1;
	t_coord					p2;
	int							index;
	float						len;
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
	t_wall					*wlist;
	t_visual				vs;
	int							lmb;//Left mouse button
	int							rmb;
	// t_coord					last_point;
	int							*icons_trash;//Иконки инструментов одним имейджем
	int							*icons_data;
	int							menu_is_open;
	int						wside;
	t_coord				click;
	int						idcurr;
	float					angle_mem;
	int						wpoint;
	int						wpoint_tmp;

	t_coord				inst_panel;
	t_coord				inst_panel_size;
	void					(*inst_func)(void *cr, int x, int y);
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
int								select_wall(t_core *cr, int x, int y);
t_wall						*find_by_index(t_core *cr, int index);
int								is_near_wall(t_wall *wall, int x, int y);
int				 				min(int a, int b);
int 							max(int a, int b);
void							draw_rectangle(t_core *cr, t_coord xy, t_coord ab, int color);
void							rmb_menu(t_core *cr, int x, int y);
void							load_gui(t_core *cr);
void							display_instruments(t_core *cr);
void							halfplane(t_core *cr, t_wall *ref);
void							reset_color(t_core *cr);
int								choose_instrument(t_core *cr, int x, int y);
void							draw_wall(void *td, int x, int y);
void							eraser(void *td, int x, int y);
void							img_fill(void *idata, int color);

#endif
