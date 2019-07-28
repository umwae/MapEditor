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

void			display_instruments(t_core *cr)
{
	mlx_put_image_to_window(cr->mlx, cr->win, cr->icons_trash, 0, WIN_HIGHT / 5);
}

void			load_gui(t_core *cr)
{
	int	x;
	int	y;
	int	i;

	i = 1;
	if (!(cr->icons_trash = (int *)malloc(sizeof(int))))
		err_ex(0);
	cr->icons_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/instruments.xpm", &x, &y);
	cr->icons_data = (int *)mlx_get_data_addr(cr->icons_trash, \
		&cr->bpp, &(cr->linesize), &(cr->endian));
}
