/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:16 by jsteuber          #+#    #+#             */
/*   Updated: 2019/08/31 18:34:38 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1500
# define WIN_HIGHT 1300

# define MAGNET_RADIUS 30
# define SELECT_RADIUS 60
# define SELECT_PADDING 30
# define POINT_SIZE 4

# define WALL_COLOR 0xECF7FF
# define SELECT_COLOR 0xFFD200
# define MENU_COLOR 0xA0A0A0
# define SEL_SEC_COLOR 0xFF3300
# define APP_SEC_COLOR 0x00FFFF
# define POINT_COLOR 0xFFFFFF
# define PORTAL_COLOR 0xA600E7
# define APP_PORTAL_COLOR 0xBF8EEA

# define PI_CEIL 4
# define PI_4 3.1415f

# define INST_PANEL_X 0
# define INST_PANEL_Y WIN_HIGHT / 5
# define INST_NUM 4
# define MENU_XLEN 300
# define MENU_YLEN 500
# define CHECKBOX_SIZE 20

# define ST_FLOOR_HIGHT 0
# define ST_CEIL_HIGHT 75

# define COMPRESSING 30

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
	int							sectors[2];
	int							isportal;
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

typedef struct		s_msg
{
	char						**text;
	t_coord					pos;
	int							color;
	int							id;
}									t_msg;

typedef struct		s_elems
{
	int							isportal;
}									t_elems;

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
	int							sectors[1000];
	t_visual				vs;
	t_elems					cmenu_elems;
	int							lmb;//Left mouse button
	int							rmb;
	// t_coord					last_point;
	void						*icons_trash;//Иконки инструментов одним имейджем
	void						*hl_trash;
	void						*icons_data;
	void						*hl_data;
	int							menu_is_open;
	int							wside;
	t_coord					click;
	int							idcurr;
	float						angle_mem;
	int							wpoint;
	int							wpoint_tmp;

	t_coord					inst_panel;
	t_coord					inst_panel_size;
	void						(*inst_func)(void *cr, int x, int y);
	int							highlight;

	t_list					**messages;

	int							sec_num;
	int							shift_button;
	int							ctrl_button;
	int							multi_sel;
	t_coord					idsec;
	t_coord					s[2];
	int							mpsw;
	//
	t_coord					offs;
	t_coord					msmem;
	float					zoom;
	int						dragl;
	int						test;

}									t_core;

void							init(t_core		*cr);
void							err_ex(int pr);
void							redraw(t_core *cr);
void							img_new(t_core *cr);
void							img_pxl(void *td, int x, int y, int color);
void							pxl_put_wrap(void *td, int x, int y, int color);
int								red_button(t_core *pr);
int								key_action(int keycode, t_core *cr);
int								key_release(int keycode, t_core *cr);
int								mouse_press(int button, int x, int y, t_core *cr);
int								mouse_release(int button, int x, int y, t_core *cr);
int								mouse_move(int x, int y, t_core *cr);
void							bresenham(t_core *cr, void (*print_func)(void *, int, int, int));
void							add_wall(t_core *cr);
void							magnet(t_core *cr, int *x, int *y, int check_start);
float							calc_dist(int x0, int y0, int x1, int y1);
int								select_wall(t_core *cr, int x, int y);
t_wall						*find_by_index(t_core *cr, int index);
int								is_near_wall(t_core *cr, t_wall *wall, int x, int y);
int				 				min(int a, int b);
int 							max(int a, int b);
void							draw_rectangle(t_core *cr, t_coord xy, t_coord ab, int color);
void							rmb_menu(t_core *cr, t_wall *wall, int x, int y);
void							load_gui(t_core *cr);
void							display_instruments(t_core *cr);
void							halfplane(t_core *cr, t_wall *ref);
void							reset_color(t_core *cr);
int								choose_instrument(t_core *cr, int x, int y);
void							draw_wall(void *td, int x, int y);
void							eraser(void *td, int x, int y);
void							img_fill(void *idata, int color);
void							show_messages(t_core *cr);
void							add_message(t_core *cr, char **text, int pos, int color, int id);
int								find_msg_by_id(t_core *cr, int id);
void							highlight(t_core *cr);
void							iter_wall(t_core *cr, int pr1, int pr2, void (*f)(t_core *, t_wall *, int, int));
void							apply_sector(t_core *cr, t_wall *wall,int color1, int color2);
void							turn_color(t_core *cr, t_wall *wall, int color1, int color2);
void							redraw_color(t_core *cr, t_wall *wall, int exception1, int exception2);
void							straight_line(t_core *cr, int *x, int *y);
void							draw_nodes(t_core *cr, t_wall *wall, int pr1, int pr2);
void							find_multi_sel(t_core *cr);
void							check_menu_events(t_core *cr, int x, int y);
void							switch_isportal(t_core *cr, t_wall *wall, int switchval, int pr2);
void							remove_sectors(t_core *cr, int id);
void 							restore_sec_id(t_core *cr);
void        	    save_map(t_core *cr);
void							load_map(t_core *cr);
void							erase_by_id(t_core	*cr, int id);
int    						find_rep_symb(char *line, char symb, int num);
t_wall						*get_last_wall(t_core *cr);
int								find_vt_id(t_core *cr, int x, int y);
void							count_sectors(t_core *cr, t_wall *wall, int pr1, int pr2);
int								check_bounds(t_core *cr, int x, int y);

#endif
