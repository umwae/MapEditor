/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/14 15:36:19 by jsteuber         ###   ########.fr       */
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
		new_sector(cr);
	else if (keycode == 257)
		cr->shift_button = 1;
	else if (keycode == 256)
		cr->ctrl_button = 1;
	else if (keycode == 1)
		save_map(cr);
	else if (keycode == 37)
		load_map(cr);
	else if (keycode == 123)
		cr->player.coord.x -= 20;
	else if (keycode == 124)
		cr->player.coord.x += 20;
	else if (keycode == 125)
		cr->player.coord.y += 20;
	else if (keycode == 126)
		cr->player.coord.y -= 20;
	else if (keycode == 67)
	{
		// del_object(cr, 2);
		cr->test *= -1;
	}
		// cr->test *= -1;
	redraw(cr);
	return (0);
}

int			mouse_move(int x, int y, t_core *cr)
{
	if (cr->dragl == 1)
	{
		cr->offs.x += x - cr->msmem.x;
		cr->offs.y += y - cr->msmem.y;
		cr->msmem.x = x;
		cr->msmem.y = y;
		redraw(cr);
	}
	else if (cr->lmb == 1)
	{
		if (cr->shift_button == 1)
			straight_line(cr, &x, &y);
		redraw(cr);
		cr->vs.x1 = x;
		cr->vs.y1 = y;
		cr->vs.x0 = cr->vs.mem_x;
		cr->vs.y0 = cr->vs.mem_y;
		cr->vs.color = WALL_COLOR;
		grid_magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
		// magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
		bresenham(cr, &pxl_put_wrap);
	}
	return (0);
}

int			mouse_release(int button, int x, int y, t_core *cr)
{
	if (button == 1)
	{
		if (button == 1)
			cr->dragl = 0;
		//
		cr->detect_cl = 0;//Переписать на !менеджер событий в инфо меню
		iter_wall(cr, SELECT_COLOR, -1, &is_there_color);
		if (cr->detect_cl == 0)
		{
			cr->i_menu_is_open = 0;
		}
		//
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
			grid_magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
			// magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
			cr->vs.x1 -= cr->offs.x;
			cr->vs.y1 -= cr->offs.y;
			cr->vs.mem_x -= cr->offs.x;
			cr->vs.mem_y -= cr->offs.y;
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

	if (button == 1 && !check_bounds(x, y))
	{
		if (!choose_instrument(cr, x, y))
		{
			// printf("NOT AN INSTRUMENT\n");
			if (cr->menu_is_open == 1)
			{
				check_menu_events(cr, x, y);
			}
			else if (cr->test == 1)
			{
				cr->msmem.x = x;
				cr->msmem.y = y;
				cr->dragl = 1;
			}
			else
			{
				(*cr->inst_func)(cr, x, y);
			}
		}
	}
	else if (button == 2 && !check_bounds(x, y))
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
	else if (button == 5)
	{
		printf("ZOOM %d\n", cr->zoom);
		cr->msmem.x = WIN_WIDTH / 2;
		cr->msmem.y = WIN_HIGHT / 2;
		if (cr->zoom < WIN_WIDTH)
			cr->zoom += cr->zoom / 2;
		cr->offs.x += (cr->offs.x / 2 - (x - cr->msmem.x) / 2);
		cr->offs.y += (cr->offs.y / 2 - (y - cr->msmem.y) / 2);
		redraw(cr);
	}
	else if (button == 4)
	{
		printf("ZOOM %d\n", cr->zoom);
		cr->msmem.x = WIN_WIDTH / 2;
		cr->msmem.y = WIN_HIGHT / 2;
		if (cr->zoom > 1)
			cr->zoom -= cr->zoom / 3;
		cr->offs.x -= cr->offs.x / 3 - (x - cr->msmem.x) / 3;
		cr->offs.y -= cr->offs.y / 3 - (y - cr->msmem.y) / 3;
		redraw(cr);
	}
	return (0);
}
