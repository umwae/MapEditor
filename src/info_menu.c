/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 20:31:13 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void			info_menu(t_core *cr, t_wall *wall)
{
	t_coord	xy;
	t_coord	ab;
	char		*text;

	if (!wall)
		return ;
	cr->i_menu_is_open = 1;
	cr->i_menu_wall = wall;
	ab.x = I_MENU_XLEN;
	ab.y = I_MENU_YLEN;
	xy.x = WIN_WIDTH - ab.x - 4;
	xy.y = 0 + 4;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	//
	text = ft_strnew(100);
	ft_strcat(text, "P1(y, x):    ");
	ft_strcat(text, ft_itoa(wall->p1.y));
	ft_strcat(text, " ");
	ft_strcat(text, ft_itoa(wall->p1.x));
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 10, \
	I_MENU_YLEN / 10, 0, text);
	ft_strclr(text);
	ft_strcat(text, "P2(y, x):    ");
	ft_strcat(text, ft_itoa(wall->p2.y));
	ft_strcat(text, " ");
	ft_strcat(text, ft_itoa(wall->p2.x));
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 10, \
	I_MENU_YLEN / 10 * 2, 0, text);
	ft_strclr(text);
	//
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, I_MENU_YLEN / 3 + 10);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, I_MENU_YLEN / 3 + 10);
	//
	ft_strcat(text, " [ ");
	ft_strcat(text, ft_itoa(wall->sectors[0].s));
	ft_strcat(text, " ]");
	ft_strcat(text, " texture: ");
	ft_strcat(text, ft_itoa(wall->sectors[0].t));
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 5, \
	I_MENU_YLEN / 3 + 10, 0, text);
	//
	ft_strclr(text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, I_MENU_YLEN / 3 + 10 + ICON_SIZE);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, I_MENU_YLEN / 3 + 10 + ICON_SIZE);
	//
	ft_strcat(text, " [ ");
	ft_strcat(text, ft_itoa(wall->sectors[1].s));
	ft_strcat(text, " ]");
	ft_strcat(text, " texture: ");
	ft_strcat(text, ft_itoa(wall->sectors[1].t));
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 5, \
	I_MENU_YLEN / 3 + 10 + ICON_SIZE, 0, text);
	//
	free(text);
}

void			check_wall_events(int x, int y, t_wall *wall)
{
	t_coord	xy;

	if (!wall)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > I_MENU_YLEN / 3 + 10 && y < I_MENU_YLEN / 3 + 10 + ICON_SIZE)
		wall->sectors[0].t--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > I_MENU_YLEN / 3 + 10 && y < I_MENU_YLEN / 3 + 10 + ICON_SIZE)
		wall->sectors[0].t++;
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > I_MENU_YLEN / 3 + 10 + ICON_SIZE && y < I_MENU_YLEN / 3 + 10 + ICON_SIZE * 2)
		wall->sectors[1].t--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > I_MENU_YLEN / 3 + 10 + ICON_SIZE && y < I_MENU_YLEN / 3 + 10 + ICON_SIZE * 2)
		wall->sectors[1].t++;
}

void			check_wall_events_mwheel(t_coord click, int button, t_wall *wall)
{
	t_coord	xy;

	if (!wall)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > I_MENU_YLEN / 3 + 10 && click.y < I_MENU_YLEN / 3 + 10 + ICON_SIZE)
	{
		if (button == 5)
			wall->sectors[0].t++;
		else if (button == 4)
			wall->sectors[0].t--;
	}
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > I_MENU_YLEN / 3 + 10 + ICON_SIZE && click.y < I_MENU_YLEN / 3 + 10 + ICON_SIZE * 2)
	{
		if (button == 5)
			wall->sectors[1].t++;
		else if (button == 4)
			wall->sectors[1].t--;
	}
}

void			obj_info_menu(t_core *cr, t_obj *obj)
{
	t_coord	xy;
	t_coord	ab;
	char		*text;

	if (!obj)
		return ;
	cr->i_menu_is_open = 2;
	ab.x = I_MENU_XLEN;
	ab.y = I_MENU_YLEN;
	xy.x = WIN_WIDTH - ab.x - 4;
	xy.y = 0 + 4;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	//
	text = ft_strnew(100);
	ft_strcat(text, " Type: ");
	ft_strcat(text, ft_itoa(obj->type));
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 3, \
	I_MENU_YLEN / 9, 0, text);
	free(text);
	//Заменить хайлайт на иконку
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, I_MENU_YLEN / 10);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, I_MENU_YLEN / 10);
}

void			check_obj_events(int x, int y, t_obj *obj)
{
	t_coord	xy;

	if (!obj)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > I_MENU_YLEN / 10 && y < I_MENU_YLEN / 10 + ICON_SIZE)
	{
		// if ()
		obj->type--;
	}
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > I_MENU_YLEN / 10 && y < I_MENU_YLEN / 10 + ICON_SIZE)
	{
		obj->type++;
	}
}

void			check_obj_events_mwheel(t_coord click, int button, t_obj *obj)
{
	t_coord	xy;

	if (!obj)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > I_MENU_YLEN / 10 && click.y < I_MENU_YLEN / 10 + LINE_SIZE_Y)
	{
		if (button == 5)
			obj->type++;
		else if (button == 4)
			obj->type--;
	}
}

// f c fi ci il fin door

void			sec_info_menu(t_core *cr, int secid)
{
	t_coord	xy;
	t_coord	ab;
	char		*text;
	t_sec		*sec;

	if (!(sec = find_sec_list(cr, secid)))
		return ;
	cr->i_menu_is_open = 4;
	ab.x = I_MENU_XLEN;
	ab.y = I_SEC_MENU_YLEN;
	xy.x = WIN_WIDTH - ab.x - 4;
	xy.y = 0 + 4;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	text = ft_strnew(100);
	//
	ft_strcat(text, "Floor lvl: ");
	ft_strcat(text, ft_ftoa(sec->floor));
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + 4), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + 4));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + ab.x - ICON_SIZE, (xy.y + 4));
	ft_strclr(text);
	//
	ft_strcat(text, "Ceiling lvl: ");
	ft_strcat(text, ft_ftoa(sec->ceiling));
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE + 8), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE + 8));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + ab.x - ICON_SIZE, (xy.y + ICON_SIZE + 8));
	ft_strclr(text);
	//
	ft_strcat(text, "Floor tex: ");
	ft_strcat(text, ft_itoa(sec->ftex));
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE * 2 + 12), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE * 2 + 12));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + ab.x - ICON_SIZE, (xy.y + ICON_SIZE * 2 + 12));
	ft_strclr(text);
	//
	ft_strcat(text, "Ceiling tex: ");
	ft_strcat(text, ft_itoa(sec->ctex));
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE * 3 + 16), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE * 3 + 16));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + ab.x - ICON_SIZE, (xy.y + ICON_SIZE * 3 + 16));
	ft_strclr(text);
	//
	ft_strcat(text, "Illumination: ");
	ft_strcat(text, ft_ftoa(sec->illum));
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE * 4 + 20), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE * 4 + 20));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + ab.x - ICON_SIZE, (xy.y + ICON_SIZE * 4 + 20));
	ft_strclr(text);
	//
	xy.x += I_MENU_XLEN / 3;
	xy.y = xy.y + ICON_SIZE * 5 + 24;
	ab.x = CHECKBOX_SIZE;
	ab.y = CHECKBOX_SIZE;
	draw_rectangle(cr, xy, ab, 0xffffff);
	ft_strcat(text, "Door");
	mlx_string_put(cr->mlx, cr->win, xy.x + CHECKBOX_SIZE + 10, \
	xy.y, 0, text);
	if (sec->isdoor == 1)
		checkbox_fill(cr, xy, ab);
	ft_strclr(text);
	//
	xy.y += LINE_SIZE_Y;
	ab.x = CHECKBOX_SIZE;
	ab.y = CHECKBOX_SIZE;
	draw_rectangle(cr, xy, ab, 0xffffff);
	ft_strcat(text, "Finish");
	mlx_string_put(cr->mlx, cr->win, xy.x + CHECKBOX_SIZE + 10, \
	xy.y, 0, text);
	if (sec->isfinish == 1)
		checkbox_fill(cr, xy, ab);
	ft_strclr(text);
	free(text);
}

void			check_sec_events_mwheel(t_core *cr, t_coord click, int button, int secid)
{
	t_coord		xy;
	t_sec		*sec;

	if (!(sec = find_sec_list(cr, secid)))
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + 4 && click.y < xy.y + 4 + ICON_SIZE)
	{
		if (button == 5)
			sec->floor++;
		else if (button == 4)
			sec->floor--;
	}
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE + 8 && click.y < xy.y + 8 + ICON_SIZE * 2)
	{
		if (button == 5)
			sec->ceiling++;
		else if (button == 4)
			sec->ceiling--;
	}
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE * 2 + 12 && click.y < xy.y + 12 + ICON_SIZE * 3)
	{
		if (button == 5)
			sec->ftex++;
		else if (button == 4)
			sec->ftex--;
	}
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE * 3 + 16 && click.y < xy.y + 16 + ICON_SIZE * 4)
	{
		if (button == 5)
			sec->ctex++;
		else if (button == 4)
			sec->ctex--;
	}
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE * 4 + 20 && click.y < xy.y + 20 + ICON_SIZE * 5)
	{
		if (button == 5)
			sec->illum += 0.1;
		else if (button == 4)
			sec->illum -= 0.1;
	}
	valid_illum_val(&sec->illum);
}

void			check_sec_events(t_core *cr, int x, int y, int secid)
{
	t_coord	xy;
	t_sec	*sec;

	if (!(sec = find_sec_list(cr, secid)))
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 4 && y < xy.y + 4 + ICON_SIZE)
		sec->floor -= 0.1;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 4 && y < xy.y + 4 + ICON_SIZE)
		sec->floor += 0.1;//
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 8 + ICON_SIZE && y < xy.y + 8 + ICON_SIZE * 2)
		sec->ceiling -= 0.1;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 8 + ICON_SIZE && y < xy.y + 8 + ICON_SIZE * 2)
		sec->ceiling += 0.1;//
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 12 + ICON_SIZE * 2 && y < xy.y + 12 + ICON_SIZE * 3)
		sec->ftex--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 12 + ICON_SIZE * 2 && y < xy.y + 12 + ICON_SIZE * 3)
		sec->ftex++;//
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 16 + ICON_SIZE * 3 && y < xy.y + 16 + ICON_SIZE * 4)
		sec->ctex--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 16 + ICON_SIZE * 3 && y < xy.y + 16 + ICON_SIZE * 4)
		sec->ctex++;//
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 20 + ICON_SIZE * 4 && y < xy.y + 20 + ICON_SIZE * 5)
		sec->illum -= 0.1;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 20 + ICON_SIZE * 4 && y < xy.y + 20 + ICON_SIZE * 5)
		sec->illum += 0.1;
	else if (x > xy.x + I_MENU_XLEN / 3 && x < xy.x + I_MENU_XLEN / 3 + CHECKBOX_SIZE && \
	y > xy.y + ICON_SIZE * 5 + 24 && y < xy.y + ICON_SIZE * 5 + 24 + CHECKBOX_SIZE)
		sec->isdoor = sec->isdoor == 0 ? 1 : 0;
	else if (x > xy.x + I_MENU_XLEN / 3 && x < xy.x + I_MENU_XLEN / 3 + CHECKBOX_SIZE && \
	y > xy.y + ICON_SIZE * 5 + 24 + LINE_SIZE_Y && y < xy.y + ICON_SIZE * 5 + 24 + CHECKBOX_SIZE + LINE_SIZE_Y)
		sec->isfinish = sec->isfinish == 0 ? 1 : 0;
	valid_illum_val(&sec->illum);
}
