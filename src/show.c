/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/06 22:12:20 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

static void		copy_vals(t_core *cr)
{
	cr->vs.x0_copy = cr->vs.x0;
	cr->vs.y0_copy = cr->vs.y0;
}

void					bresenham(t_core *cr, void (*print_func)(void *, int, int, int))
{
	int	sx;
	int	err;
	int	sy;
	int	e2;

	copy_vals(cr);
	if (cr->vs.x1 <= 0 || cr->vs.x1 > WIN_WIDTH || cr->vs.y1 <= 0 || cr->vs.y1 > WIN_HIGHT ||
	cr->vs.x0_copy <= 0 || cr->vs.x0_copy > WIN_WIDTH || cr->vs.y0_copy <= 0 || cr->vs.y0_copy > WIN_HIGHT)
	{
		printf("??? %d %d %d %d\n", cr->vs.x0_copy, cr->vs.y0_copy, cr->vs.x1, cr->vs.y1);
	fflush(stdout);
	return ;
	}
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

static void			draw_walls(t_core *cr, t_sector *sec)
{
	t_wall	*wall;

	wall = sec->walls;
	while (wall)
	{
		cr->vs.x0 = wall->p1.x;
		cr->vs.y0 = wall->p1.y;
		cr->vs.x1 = wall->p2.x;
		cr->vs.y1 = wall->p2.y;
		bresenham(cr, &img_pxl);
		wall = wall->next;
	}
}

static void			draw_sectors(t_core *cr)
{
	t_sector	*sec;

	sec = cr->sectors;
	while (sec)
	{
		draw_walls(cr, sec);
		sec = sec->next;
	}
}

void			redraw(t_core *cr)
{
	// mlx_destroy_image(cr->mlx, cr->image);
	// img_new(cr);
	mlx_clear_window(cr->mlx, cr->win);
	// img_pxl(cr, 100, 100, 0xffffff);
	// cr->sectors->walls->p1.x = 200;
	// cr->sectors->walls->p1.y = 200;
	// cr->sectors->walls->p2.x = 220;
	// cr->sectors->walls->p2.y = 330;
	// minimap_init(cr);
	draw_sectors(cr);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->image, 0, 0);
}
