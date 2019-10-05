/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:17:36 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

void					draw_nodes(t_core *cr, t_wall *wall, int pr1, int pr2)
{
	t_coord		xy;
	t_coord		ab;

	(void)pr1;
	(void)pr2;
	ab.x = POINT_SIZE;
	ab.y = POINT_SIZE;
	xy.x = wall->p1.x - POINT_SIZE / 2;
	xy.y = wall->p1.y - POINT_SIZE / 2;
	draw_rectangle_img_pxl(cr, xy, ab, POINT_COLOR);
	xy.x = wall->p2.x - POINT_SIZE / 2;
	xy.y = wall->p2.y - POINT_SIZE / 2;
	draw_rectangle_img_pxl(cr, xy, ab, POINT_COLOR);
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

void			redraw(t_core *cr)
{
	mlx_clear_window(cr->mlx, cr->win);
	img_fill(cr->idata, 0x000000);
	grid(cr);
	draw_walls(cr);
	iter_wall(cr, 0, 0, &draw_nodes);
	draw_objects(cr);
	draw_player(cr);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->image, 0, 0);
	print_sec_num(cr);
	draw_objects_text(cr);
	display_instruments(cr);
	highlight(cr);
	spot_sector_around(cr, &cr->player);
	if (cr->i_menu_is_open == 1)
		info_menu(cr, cr->i_menu_wall);
	else if (cr->i_menu_is_open == 2)
		obj_info_menu(cr, cr->closest_obj);
	else if (cr->i_menu_is_open == 4)
		sec_info_menu(cr, cr->sel_sec_id);
}
