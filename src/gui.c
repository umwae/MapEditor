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

void	draw_wall(void *td, int x, int y)
{
	t_core	*cr;

	cr = td;
	if (cr->menu_is_open == 1)
		return ;
	cr->lmb = 1;
	cr->vs.x0 = x;
	cr->vs.y0 = y;
	cr->vs.x1 = x;
	cr->vs.y1 = y;
	magnet(cr, &cr->vs.x0, &cr->vs.y0, 0);
	cr->vs.mem_x = cr->vs.x0;
	cr->vs.mem_y = cr->vs.y0;
}

void	eraser(void *td, int x, int y)
{
	t_core	*cr;
	int			id;
	t_wall	*wall;
	t_wall	*rm;

	cr = td;
	id = select_wall(cr, x, y);
	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall->next)
	{
		if (((t_wall *)wall->next)->index == id)
		{
			rm = wall->next;
			wall->next = ((t_wall *)wall->next)->next;
			free(rm);
			return ;
		}
		wall = wall->next;
	}
	wall = cr->wlist;
	while (wall)
	{
		printf("%d\n", wall->index);
		wall = wall->next;
	}
	redraw(cr);
}

int			choose_instrument(t_core *cr, int x, int y)
{
	// printf("%d %d\n", cr->inst_panel_size.x, cr->inst_panel_size.y);
	if (!(x > cr->inst_panel.x && x < cr->inst_panel_size.x && \
		y > cr->inst_panel.y && y < cr->inst_panel.y + cr->inst_panel_size.y))
		return (0);
	if (y > cr->inst_panel.y && y < cr->inst_panel.y + cr->inst_panel_size.y / 2)
		cr->inst_func = draw_wall;
	if (y > cr->inst_panel.y + cr->inst_panel_size.y / 2 && y < cr->inst_panel.y + cr->inst_panel_size.y)
		cr->inst_func = eraser;
	return (1);
	// printf("HH\n");
}

void			display_instruments(t_core *cr)
{
	mlx_put_image_to_window(cr->mlx, cr->win, cr->icons_trash, \
		cr->inst_panel.x, cr->inst_panel.y);
}

void			load_gui(t_core *cr)
{
	int	i;

	i = 1;
	if (!(cr->icons_trash = (int *)malloc(sizeof(int))))
		err_ex(0);
	cr->icons_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/instruments.xpm", \
	&cr->inst_panel_size.x, &cr->inst_panel_size.y);
	cr->icons_data = (int *)mlx_get_data_addr(cr->icons_trash, \
		&cr->bpp, &(cr->linesize), &(cr->endian));
	cr->inst_panel.x = INST_PANEL_X;
	cr->inst_panel.y = INST_PANEL_Y;
}
