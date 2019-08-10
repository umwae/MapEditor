/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/31 19:30:02 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "editor.h"

int			red_button(t_core *pr)
{
	(void)pr;
	exit(0);
}

int			key_release(int keycode, t_core *cr)
{
	if (keycode == 257)
		cr->shift_button = 0;
	else if (keycode == 256)
		cr->ctrl_button = 0;
	return (0);
}

int			key_action(int keycode, t_core *cr)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 16)
	{
		iter_wall(cr, -1, -1, &apply_sector);
		cr->sec_num++;
		iter_wall(cr, -1, -1, &redraw_color);
	}
	else if (keycode == 257)
		cr->shift_button = 1;
	else if (keycode == 256)
		cr->ctrl_button = 1;
	else if (keycode == 1)
		save_map(cr);
	redraw(cr);
	return (0);
}

int			mouse_move(int x, int y, t_core *cr)
{
	if (cr->lmb == 1)
	{
		if (cr->shift_button == 1)
			straight_line(cr, &x, &y);
		redraw(cr);
		cr->vs.x1 = x;
		cr->vs.y1 = y;
		cr->vs.x0 = cr->vs.mem_x;
		cr->vs.y0 = cr->vs.mem_y;
		cr->vs.color = WALL_COLOR;
		magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
		bresenham(cr, &pxl_put_wrap);
	}
	return (0);
}

int			mouse_release(int button, int x, int y, t_core *cr)
{
	if (button == 1)
	{
		if (cr->menu_is_open == 1)
		{
			cr->menu_is_open = 0;
			redraw(cr);
			return (0);
		}
		if (cr->lmb == 1)
		{
			cr->lmb = 0;
			if (cr->shift_button == 1)
				straight_line(cr, &x, &y);
			cr->vs.x1 = x;
			cr->vs.y1 = y;
			magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
			add_wall(cr);
		}
	}
	else if (button == 2)
	{
		cr->rmb = 0;
		return (0);
	}
	else
		return (0);
	redraw(cr);
	return (0);
}

int			mouse_press(int button, int x, int y, t_core *cr)
{
	int		wall_id;

	if (button == 1)
	{
		if (!choose_instrument(cr, x, y))
		{
			// printf("NOT AN INSTRUMENT\n");
			(*cr->inst_func)(cr, x, y);
			if (cr->menu_is_open == 1)
			{
				check_menu_events(cr, x, y);
			}
		}
	}
	else if (button == 2)
	{
		cr->rmb = 1;
		find_multi_sel(cr);
		if ((wall_id = select_wall(cr, x, y)) >= 0)
		{
			find_by_index(cr, wall_id)->color = SELECT_COLOR;
			redraw(cr);
			rmb_menu(cr, find_by_index(cr, wall_id), x, y);
		}
		cr->multi_sel = 0;
	}
	return (0);
}
