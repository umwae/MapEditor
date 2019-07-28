/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/26 19:43:26 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void			draw_rectangle(t_core *cr, t_coord xy, t_coord ab, int color)
{
	int		c_abx;

	while (ab.y--)
	{
		c_abx = ab.x;
		while (c_abx--)
		{
			pxl_put_wrap(cr, xy.x + c_abx, xy.y + ab.y, color);
		}
	}
}

void			rmb_menu(t_core *cr, int x, int y)
{
	t_coord	xy;
	t_coord	ab;

	cr->menu_is_open = 1;
	xy.x = x;
	xy.y = y;
	ab.x = 300;
	ab.y = 500;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
}
