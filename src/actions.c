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

int			key_action(int keycode, t_core *cr)
{
	if (keycode == 53)
		exit(0);
	// else if (keycode == 0)
	// {
	//
	// }
	redraw(cr);
	return (0);
}

int			mouse_move(int x, int y, t_core *cr)
{
	if (cr->lmb == 1)
	{
		redraw(cr);
		cr->vs.x1 = x;
		cr->vs.y1 = y;
		cr->vs.x0 = cr->vs.mem_x;
		cr->vs.y0 = cr->vs.mem_y;
		cr->vs.color = WALL_COLOR;
		magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
		bresenham(cr, &pxl_put_wrap);
	}
	// redraw(cr);
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
	if (button == 1)
	{
		if (!choose_instrument(cr, x, y))
			(*cr->inst_func)(cr, x, y);
	}
	else if (button == 2)
	{
		cr->rmb = 1;

		if (select_wall(cr, x, y) >= 0)
		{
			find_by_index(cr, select_wall(cr, x, y))->color = SELECT_COLOR;
			redraw(cr);
			rmb_menu(cr, x, y);
		}
	}
	return (0);
}
