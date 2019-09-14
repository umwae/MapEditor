/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/14 16:49:10 by jsteuber         ###   ########.fr       */
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
	printf("DDDDDDDDDDDDDDDDD %s\n", text);
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 10, \
	I_MENU_YLEN / 10, 0, text);
	ft_strclr(text);
	ft_strcat(text, "P2(y, x):    ");
	ft_strcat(text, ft_itoa(wall->p2.y));
	ft_strcat(text, " ");
	ft_strcat(text, ft_itoa(wall->p2.x));
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 10, \
	I_MENU_YLEN / 10 * 2, 0, text);
	free(text);



	ft_strcat(text, ft_ftoa((float)wall->p1.y / cr->zoom * UNIT_SIZE));
	int			find_vt_id(t_core *cr, float x, float y)
}
