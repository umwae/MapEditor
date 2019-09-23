/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/20 20:33:44 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

void					draw_nodes(t_core *cr, t_wall *wall, int pr1, int pr2)
{
// 	t_coord		xy;
// 	t_coord		ab;
//
// 	(void)pr1;
// 	(void)pr2;
// 	ab.x = POINT_SIZE;
// 	ab.y = POINT_SIZE;
// 	xy.x = wall->p1.x - POINT_SIZE / 2 + cr->offs.x;
// 	xy.y = wall->p1.y - POINT_SIZE / 2 + cr->offs.y;
// 	draw_rectangle(cr, xy, ab, POINT_COLOR);
// 	xy.x = wall->p2.x - POINT_SIZE / 2 + cr->offs.x;
// 	xy.y = wall->p2.y - POINT_SIZE / 2 + cr->offs.y;
// 	draw_rectangle(cr, xy, ab, POINT_COLOR);
// //
// 	char *txt = malloc(sizeof(char) * 5);//Отображает номера стен, вызывает тормоза
	// ft_strcpy(txt, ft_itoa(wall->index));
	// mlx_string_put(cr->mlx, cr->win, min(wall->p2.x + cr->offs.x, wall->p1.x + cr->offs.x) + abs(wall->p2.x - wall->p1.x) / 2, \
	// min(wall->p2.y + cr->offs.y, wall->p1.y + cr->offs.y) + abs(wall->p2.y - wall->p1.y) / 2, 0xffffff, txt);
//
	// char *txt = malloc(sizeof(char) * 5);//Отображает номера секторов, вызывает тормоза
	// ft_strcpy(txt, ft_strjoin(ft_strjoin(ft_itoa(wall->sectors[0].s), " "), ft_itoa(wall->sectors[1].s)));
	// mlx_string_put(cr->mlx, cr->win, min(wall->p2.x, wall->p1.x) + abs(wall->p2.x - wall->p1.x) / 2 + cr->offs.x, \
	// min(wall->p2.y, wall->p1.y) + abs(wall->p2.y - wall->p1.y) / 2 + cr->offs.y, 0xffffff, txt);

	// char *txt = malloc(sizeof(char) * 5);//Отображает номера точек друг поверх друга
	// ft_strcpy(txt, ft_itoa(find_vt_id(cr, wall->p1.x / cr->zoom * UNIT_SIZE, wall->p1.y / cr->zoom * UNIT_SIZE)));
	// mlx_string_put(cr->mlx, cr->win, wall->p1.x + cr->offs.x, wall->p1.y + cr->offs.y, 0xffffff, txt);
	// ft_strcpy(txt, ft_itoa(find_vt_id(cr, wall->p2.x / cr->zoom * UNIT_SIZE, wall->p2.y / cr->zoom * UNIT_SIZE)));
	// mlx_string_put(cr->mlx, cr->win, wall->p2.x + cr->offs.x, wall->p2.y + cr->offs.y, 0xffffff, txt);

	print_sec_num(cr);
}

void					straight_line(t_core *cr, int *x, int *y)
{
	int		dx;
	int		dy;
	float	m;

	dx = abs(*x - cr->vs.mem_x);
	dy = abs(*y - cr->vs.mem_y);
	if (dx == 0 || dy == 0)
		return;
	m = atan2(abs(dy), abs(dx));
	if (m > 0 && m < (PI_4 / 2) / 3)
		*y = cr->vs.mem_y;
	else if (m > (PI_4 / 2) / 3 * 2 && m < (PI_4 / 2))
		*x = cr->vs.mem_x;
	else
	{
		*x = *x - cr->vs.mem_x > 0  ? cr->vs.mem_x + \
		(dx + dy) / 2 : cr->vs.mem_x - (dx + dy) / 2;
		*y = *y - cr->vs.mem_y > 0 ? cr->vs.mem_y + \
		(dx + dy) / 2 : cr->vs.mem_y - (dx + dy) / 2;
	}
}

static void		copy_vals(t_core *cr)
{
	cr->vs.x0_copy = cr->vs.x0;
	cr->vs.y0_copy = cr->vs.y0;
}

void			bresenham(t_core *cr, void (*print_func)(void *, int, int, int))
{
	int	sx;
	int	err;
	int	sy;
	int	e2;

	copy_vals(cr);
	// if (cr->vs.x1 <= 0 || cr->vs.x1 > WIN_WIDTH || cr->vs.y1 <= 0 || cr->vs.y1 > WIN_HIGHT ||
	// cr->vs.x0_copy <= 0 || cr->vs.x0_copy > WIN_WIDTH || cr->vs.y0_copy <= 0 || cr->vs.y0_copy > WIN_HIGHT)
	// {
	// 	printf("??? %d %d %d %d\n", cr->vs.x0_copy, cr->vs.y0_copy, cr->vs.x1, cr->vs.y1);
	// fflush(stdout);
	// return ;
	// }
	// printf("%d %d : %d %d\n", cr->vs.x0_copy, cr->vs.y0_copy, cr->vs.x1, cr->vs.y1);
	cr->vs.dx = abs(cr->vs.x1 - cr->vs.x0_copy);
	cr->vs.dy = abs(cr->vs.y1 - cr->vs.y0_copy);
	sx = cr->vs.x0_copy < cr->vs.x1 ? 1 : -1;
	sy = cr->vs.y0_copy < cr->vs.y1 ? 1 : -1;
	err = (cr->vs.dx > cr->vs.dy ? cr->vs.dx : -cr->vs.dy) / 2;
	while (cr->vs.x0_copy != cr->vs.x1 || cr->vs.y0_copy != cr->vs.y1)
	{
		(*print_func)((void *)cr, cr->vs.x0_copy, cr->vs.y0_copy, cr->vs.color);
		e2 = err;
		if (e2 > -cr->vs.dx)
		{
			err -= cr->vs.dy;
			cr->vs.x0_copy += sx;
		}
		if (e2 < cr->vs.dy)
		{
			err += cr->vs.dx;
			cr->vs.y0_copy += sy;
		}
	}
}

static void		draw_walls(t_core *cr)
{
	t_wall	*wall;

	wall = cr->wlist;
	while (wall)
	{
		cr->vs.x0 = wall->p1.x;
		cr->vs.y0 = wall->p1.y;
		cr->vs.x1 = wall->p2.x;
		cr->vs.y1 = wall->p2.y;
		cr->vs.color = wall->color;
		bresenham(cr, &img_pxl);
		wall = wall->next;
	}
}

static void				gridtest(t_core *cr)
{
	int    xi;
	int    yi;
	int		xi2;

	xi = 0;
	yi = cr->zoom;
	while (xi <= WIN_WIDTH)
	{
		xi2 = xi - (xi) % cr->zoom;
		cr->vs.x0 = -cr->zoom + cr->offs.x % cr->zoom + xi2 - cr->offs.x;
		cr->vs.y0 = -cr->zoom + cr->offs.y % cr->zoom - cr->offs.y;
		cr->vs.x1 = -cr->zoom + cr->offs.x % cr->zoom + xi2 - cr->offs.x;
		cr->vs.y1 = WIN_HIGHT + cr->zoom + cr->offs.y % cr->zoom - cr->offs.y;
		cr->vs.color = 0x00ff00;
		bresenham(cr, &img_pxl);
		xi += 1;
	}
}

void			redraw(t_core *cr)
{
	mlx_clear_window(cr->mlx, cr->win);
	img_fill(cr->idata, 0x000000);
	// gridtest(cr);
	grid(cr);
	draw_walls(cr);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->image, 0, 0);
	iter_wall(cr, 0, 0, &draw_nodes);
	draw_objects(cr);
	draw_player(cr);
	display_instruments(cr);
	highlight(cr);
	spot_sector_around(cr, &cr->player);
	if (cr->i_menu_is_open == 1)
		info_menu(cr, cr->i_menu_wall);
	else if (cr->i_menu_is_open == 2)
		obj_info_menu(cr, cr->closest_obj);
	else if (cr->i_menu_is_open == 4)
		sec_info_menu(cr, cr->sel_sec_id);
	// show_messages(cr);
}
