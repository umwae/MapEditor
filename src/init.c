/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/31 17:58:43 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "editor.h"
#include <time.h>
#include <stdio.h>

void		init(t_core		*cr)
{
	if (!(cr->mlx = mlx_init()))
		err_ex(0);
	if (!(cr->win = mlx_new_window(cr->mlx, WIN_WIDTH, WIN_HIGHT, "Editor")))
		err_ex(0);
	// if (!(cr->sectors = (t_wall *)malloc(sizeof(t_wall))))
	// 	err_ex(0);
	// cr->sectors->next = NULL;
	// cr->sectors->walls = NULL;
	cr->wlist = NULL;
	cr->links = (t_wlink **)malloc(sizeof(t_wlink *) * 100);
	// cr->links[0] = NULL;
	load_gui(cr);
	img_new(cr);
	redraw(cr);
}
