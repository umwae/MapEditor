/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/11 19:42:37 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"

void			grid_magnet(t_core *cr, int *x, int *y, int check_start)
{
	(void)check_start;//Дописать
	int		hx;
	int *p;
	*x = (cr->offs.x + *x) / cr->zoom * cr->zoom;
	*y = (cr->offs.y + *y) / cr->zoom * cr->zoom;

	*x = *x + (cr->offs.x - WIN_WIDTH / 2) % cr->zoom + cr->zoom / 2 - \
	cr->offs.x / cr->zoom * cr->zoom - cr->zoom;
	// printf("___%d %d\n", (cr->offs.x - WIN_WIDTH / 2) % cr->zoom, *x);
	// if (abs((*x + cr->offs.x - WIN_WIDTH / 2) % cr->zoom) > cr->zoom / 2)
	// 	*x += cr->zoom;
	*y = *y + (cr->offs.y - WIN_HIGHT / 2) % cr->zoom + cr->zoom / 2 - \
	cr->offs.y / cr->zoom * cr->zoom - cr->zoom;
	// cr->vs.x1 = *x + (cr->offs.x - WIN_WIDTH / 2) % cr->zoom + cr->zoom / 2 - cr->offs.x / cr->zoom * cr->zoom;
	// cr->vs.y1 = *y + (cr->offs.y - WIN_HIGHT / 2) % cr->zoom + cr->zoom / 2 - cr->offs.y / cr->zoom * cr->zoom;
	// cr->vs.color = 0x00ff00;
	// bresenham(cr, &img_pxl);
}

void			grid(t_core *cr)
{
  int    xi;
  int    yi;

	xi = 0;
  yi = cr->zoom;
  while (yi <= WIN_HIGHT)
  {
    cr->vs.x0 = -cr->zoom + cr->offs.x % cr->zoom - cr->offs.x;
    cr->vs.y0 = -cr->zoom + cr->offs.y % cr->zoom + yi - cr->offs.y;
    cr->vs.x1 = WIN_WIDTH + cr->zoom + cr->offs.x % cr->zoom - cr->offs.x;
    cr->vs.y1 = -cr->zoom + cr->offs.y % cr->zoom + yi - cr->offs.y;
    cr->vs.color = GRID_COLOR;
    bresenham(cr, &img_pxl);
    yi += cr->zoom;
  }
  while (xi <= WIN_WIDTH)
  {
    cr->vs.x0 = -cr->zoom + cr->offs.x % cr->zoom + xi - cr->offs.x;
    cr->vs.y0 = -cr->zoom + cr->offs.y % cr->zoom - cr->offs.y;
    cr->vs.x1 = -cr->zoom + cr->offs.x % cr->zoom + xi - cr->offs.x;
    cr->vs.y1 = WIN_HIGHT + cr->zoom + cr->offs.y % cr->zoom - cr->offs.y;
    cr->vs.color = GRID_COLOR;
    bresenham(cr, &img_pxl);
    xi += cr->zoom;
  }
}
