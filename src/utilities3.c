/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 20:53:21 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <fcntl.h>

void		checkbox_fill(t_core *cr, t_coord xy, t_coord ab)
{
	xy.x = xy.x + ab.x * 0.1;
	xy.y = xy.y + ab.y * 0.1;
	ab.x *= 0.8;
	ab.y *= 0.8;
	draw_rectangle(cr, xy, ab, 0);
}

void		draw_rectangle(t_core *cr, t_coord xy, t_coord ab, int color)
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

void		draw_rectangle_img_pxl(t_core *cr, t_coord xy, t_coord ab, \
int color)
{
	int		c_abx;

	while (ab.y--)
	{
		c_abx = ab.x;
		while (c_abx--)
		{
			img_pxl(cr, xy.x + c_abx, xy.y + ab.y, color);
		}
	}
}
