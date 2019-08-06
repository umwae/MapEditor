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

void			switch_isportal(t_core *cr, t_wall *wall, int switchval, int pr2)
{
	(void)pr2;
	if (wall->color != SELECT_COLOR)
		return ;
	wall->isportal = switchval;
	if (switchval == 1)
		wall->color = PORTAL_COLOR;
	else
		wall->color = wall->sectors[0] < 0 && wall->sectors[1] < 0 ? WALL_COLOR : APP_SEC_COLOR;
}

void			check_menu_events(t_core *cr, int x, int y)
{
	if (x > cr->click.x + MENU_XLEN / 7 && x < cr->click.x + MENU_XLEN / 7 + CHECKBOX_SIZE && \
	y > cr->click.y + MENU_YLEN / 14 && y < cr->click.y + MENU_YLEN / 14 + CHECKBOX_SIZE)
	{
		// printf("MENU CLICK\n");
		if (cr->cmenu_elems.isportal == 1)
			iter_wall(cr, 0, 0, &switch_isportal);
		else
			iter_wall(cr, 1, 0, &switch_isportal);
		cr->cmenu_elems.isportal = cr->cmenu_elems.isportal > 0 ? 0 : 1;
	}
}

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

void			rmb_menu(t_core *cr, t_wall *wall, int x, int y)
{
	t_coord	xy;
	t_coord	ab;
	char		*text;


	cr->menu_is_open = 1;
	cr->click.x = x;
	cr->click.y = y;
	xy.x = x;
	xy.y = y;
	ab.x = MENU_XLEN;
	ab.y = MENU_YLEN;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	xy.x = x + MENU_XLEN / 7;
	xy.y = y + MENU_YLEN / 14;
	ab.x = CHECKBOX_SIZE;
	ab.y = CHECKBOX_SIZE;
	draw_rectangle(cr, xy, ab, 0xffffff);
	text = (char *)malloc(sizeof(char) * 7);
	ft_strcpy(text, "Portal");
	mlx_string_put(cr->mlx, cr->win, x + MENU_XLEN / 7 + ab.x * 2, \
	y + MENU_YLEN / 14, 0, text);
	if (wall->isportal == 1)
	{
		xy.x = xy.x + ab.x * 0.1;
		xy.y = xy.y + ab.y * 0.1;
		ab.x *= 0.8;
		ab.y *= 0.8;
		draw_rectangle(cr, xy, ab, 0);
		cr->cmenu_elems.isportal = 1;
	}
	else
		cr->cmenu_elems.isportal = 0;
}
