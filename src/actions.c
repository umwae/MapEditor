/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/26 18:22:05 by jsteuber         ###   ########.fr       */
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
		magnet(cr, &cr->vs.x1, &cr->vs.y1);
		bresenham(cr, &pxl_put_wrap);
	}
	// redraw(cr);
	return (0);
}

int			mouse_release(int button, int x, int y, t_core *cr)
{
	if (button == 1)
	{
		cr->lmb = 0;
		cr->vs.x1 = x;
		cr->vs.y1 = y;
		magnet(cr, &cr->vs.x1, &cr->vs.y1);
		add_wall(cr);
	}
	else if (button == 2)
	{
		cr->rmb = 0;
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
		cr->lmb = 1;
		cr->vs.x0 = x;
		cr->vs.y0 = y;
		cr->vs.x1 = x;
		cr->vs.y1 = y;
		magnet(cr, &cr->vs.x0, &cr->vs.y0);
		cr->vs.mem_x = cr->vs.x0;
		cr->vs.mem_y = cr->vs.y0;
		// printf("MOUSE_PRESS %d %d %d %d\n", );
	}
	else if (button == 2)
	{
		cr->rmb = 1;
	}
	return (0);
}
