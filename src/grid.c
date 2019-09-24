/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:18:56 by jsteuber         ###   ########.fr       */
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

	int xm;
	int ym;

	printf("___%d\n", cr->offs.x + *x - WIN_WIDTH);

	xm = *x;
	ym = *y;
	*x = (cr->offs.x + *x) / cr->zoom * cr->zoom;
	*y = (cr->offs.y + *y) / cr->zoom * cr->zoom;

	*x += -(cr->offs.x / cr->zoom * cr->zoom) + cr->zoom / 2;
	*y += -(cr->offs.y / cr->zoom * cr->zoom) + cr->zoom / 2;

	// cr->vs.x0 = *x;
	// cr->vs.y0 = *y;
	// cr->vs.x1 = *x;
	// cr->vs.y1 = *y + 200;
	// cr->vs.color = 0x00ff00;
	// bresenham(cr, &img_pxl);

	*x += (cr->offs.x - WIN_WIDTH / 2) % cr->zoom;
	*y += (cr->offs.y - WIN_HIGHT / 2) % cr->zoom;
}

void			grid(t_core *cr)
{
  int    xi;
  int    yi;

	xi = 0;
  yi = cr->zoom;
  while (yi <= WIN_HIGHT + cr->zoom)
  {
    cr->vs.x0 = -cr->zoom + cr->offs.x % cr->zoom - cr->offs.x;
    cr->vs.y0 = -cr->zoom + cr->offs.y % cr->zoom + yi - cr->offs.y;
    cr->vs.x1 = cr->zoom + WIN_WIDTH + (cr->offs.x) % cr->zoom - cr->offs.x;
    cr->vs.y1 = -cr->zoom + cr->offs.y % cr->zoom + yi - cr->offs.y;
    cr->vs.color = GRID_COLOR;
    bresenham(cr, &img_pxl);
    yi += cr->zoom;
  }
  while (xi <= WIN_WIDTH + cr->zoom * 3)
  {
    cr->vs.x0 = -cr->zoom + cr->offs.x % cr->zoom + xi - cr->offs.x;
    cr->vs.y0 = -cr->zoom + cr->offs.y % cr->zoom - cr->offs.y;
    cr->vs.x1 = -cr->zoom + cr->offs.x % cr->zoom + xi - cr->offs.x;
    cr->vs.y1 = cr->zoom + WIN_HIGHT + (cr->offs.y) % cr->zoom - cr->offs.y;
    cr->vs.color = GRID_COLOR;
    bresenham(cr, &img_pxl);
    xi += cr->zoom;
  }
}
