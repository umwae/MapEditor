/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/14 15:20:08 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void				highlight(t_core *cr)
{
	t_coord		pos;

	if (!cr->highlight)
		return ;
	pos.y =	cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * (cr->highlight - 1);
	pos.x = cr->inst_panel.x;
	mlx_put_image_to_window(cr->mlx, cr->win, cr->hl_trash, pos.x, pos.y);
}

static void	find_sector(void *td, int x, int y)
{
	t_core	*cr;
	char		*text;
	int			wall_id;

	cr = td;
	if ((wall_id = select_wall(cr, x, y)) >= 0)
	{
		iter_wall(cr, APP_SEC_COLOR, 0, &redraw_color);
		cr->click.x = x;
		cr->click.y = y;
		cr->wpoint = 2;
		// printf("---------------------SEL SEC CLICK---------------------\n");
		halfplane(cr, find_by_index(cr, wall_id));
		//
		if (!find_msg_by_id(cr, 0))
		{
			text = malloc(sizeof(char) * ft_strlen("Y to apply") + 1);
			ft_strcpy(text, "Y to apply");
			add_message(cr, &text, 2, 0xffffff, 0);
		}
	}
}

static void	select_wall_wrap(void *td, int x, int y)
{
	t_core	*cr;
	t_wall	*wall;

	cr = td;
	if (select_wall(cr, x, y) >= 0)
	{
		wall = find_by_index(cr, select_wall(cr, x, y));
		wall->color = SELECT_COLOR;
		info_menu(cr, wall);
	}
}

void				draw_wall(void *td, int x, int y)
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
	// cr->vs.x0 = x + cr->offs.x - WIN_WIDTH / 2;
	// cr->vs.y0 = y + cr->offs.y - WIN_HIGHT / 2;
	// cr->vs.x1 = x + cr->offs.x - WIN_WIDTH / 2;
	// cr->vs.y1 = y + cr->offs.y - WIN_HIGHT / 2;
	grid_magnet(cr, &cr->vs.x0, &cr->vs.y0, 0);
	// magnet(cr, &cr->vs.x0, &cr->vs.y0, 0);
	cr->vs.mem_x = cr->vs.x0;
	cr->vs.mem_y = cr->vs.y0;
}



static			void restore_id(t_core *cr)
{
	t_wall		*wall;
	int				i;

	i = 0;
	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		wall->index = i;
		i++;
		wall = wall->next;
	}
}

void						erase_by_id(t_core	*cr, int id)
{
	t_wall	*wall;
	t_wall	*rm;

	wall = cr->wlist;
	if (!wall)
		return ;
	if (!wall->next)
	{
		free(wall);
		cr->wlist = NULL;
		return ;
	}
	if (id == 0)
	{
		remove_sectors(cr, id);
		rm = wall;
		cr->wlist = wall->next;
		free(rm);
		restore_id(cr);
		restore_sec_id_v2(cr);
		return ;
	}
	while (wall->next)
	{
		if (((t_wall *)wall->next)->index == id)
		{
			remove_sectors(cr, id);
			rm = wall->next;
			wall->next = ((t_wall *)wall->next)->next;
			free(rm);
			restore_id(cr);
			restore_sec_id_v2(cr);
			return ;
		}
		wall = wall->next;
	}
	redraw(cr);
}

void				eraser(void *td, int x, int y)
{
	t_core	*cr;
	int			id;

	cr = td;
	id = select_wall(cr, x, y);
	erase_by_id(cr, id);
}

int					choose_instrument(t_core *cr, int x, int y)
{
	int		inst_num;

	inst_num = 0;
	if (!(x > cr->inst_panel.x && x < cr->inst_panel_size.x && \
		y > cr->inst_panel.y && y < cr->inst_panel.y + cr->inst_panel_size.y))
		return (0);
	else if (y > cr->inst_panel.y && y < cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM)
	{
		cr->inst_func = draw_wall;
		inst_num = 1;
	}
	else if (y > cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM && y < \
		cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 2)
	{
		cr->inst_func = eraser;
		inst_num = 2;
	}
	else if (y > cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 2 && y < \
		cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 3)
	{
		cr->inst_func = select_wall_wrap;
		inst_num = 3;
	}
	else if (y > cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 3 && y < \
		cr->inst_panel.y + cr->inst_panel_size.y)
	{
		cr->inst_func = find_sector;
		inst_num = 4;
	}
	cr->highlight = inst_num;
	return (1);
}

void				display_instruments(t_core *cr)
{
	mlx_put_image_to_window(cr->mlx, cr->win, cr->icons_trash, \
		cr->inst_panel.x, cr->inst_panel.y);
}

void				load_gui(t_core *cr)
{
	int	i;
	int	x;
	int	y;

	i = 1;
	if (!(cr->icons_trash = (int *)malloc(sizeof(int))))
		err_ex(0);
	cr->icons_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/instruments.xpm", \
	&cr->inst_panel_size.x, &cr->inst_panel_size.y);
	cr->icons_data = (int *)mlx_get_data_addr(cr->icons_trash, \
		&cr->bpp, &(cr->linesize), &(cr->endian));
	cr->inst_panel.x = INST_PANEL_X;
	cr->inst_panel.y = INST_PANEL_Y;
	//
	if (!(cr->hl_trash = (int *)malloc(sizeof(int))))
		err_ex(0);
	cr->hl_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/highlight.xpm", \
	&x, &y);
	cr->hl_data = (int *)mlx_get_data_addr(cr->hl_trash, \
	&cr->bpp, &(cr->linesize), &(cr->endian));
	//
	if (!(cr->arrowl_trash = (int *)malloc(sizeof(int))))
		err_ex(0);
	if (!(cr->arrowr_trash = (int *)malloc(sizeof(int))))
		err_ex(0);
	cr->arrowl_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/arrow_left.xpm", \
	&x, &y);
	cr->arrowr_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/arrow_right.xpm", \
	&x, &y);
	cr->arrowl_data = (int *)mlx_get_data_addr(cr->arrowl_trash, \
	&cr->bpp, &(cr->linesize), &(cr->endian));
	cr->arrowr_data = (int *)mlx_get_data_addr(cr->arrowr_trash, \
	&cr->bpp, &(cr->linesize), &(cr->endian));
}
