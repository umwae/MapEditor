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
#include <fcntl.h> 
#include "stdlib.h"
#include "math.h"

static void			write_wall(t_core *cr, char *line, int fd)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return;
	while (wall)
	{
    ft_strcpy(line, "v ");
    ft_putstr_fd(line, fd);
		ft_strcpy(line, ft_itoa(wall->p1.x));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " ");
    ft_putstr_fd(line, fd);
    ft_strcpy(line, ft_itoa(wall->p1.y));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " \n");
    ft_putstr_fd(line, fd);
    //
    ft_strcpy(line, "v ");
    ft_putstr_fd(line, fd);
    ft_strcpy(line, ft_itoa(wall->p2.x));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " ");
    ft_putstr_fd(line, fd);
    ft_strcpy(line, ft_itoa(wall->p2.y));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " \n");
    ft_putstr_fd(line, fd);
		wall = wall->next;
	}
}

void            save_map(t_core *cr)
{
  int   fd;
  char  *line;

  line = (char *)malloc(sizeof(char) * ft_strlen("v 0000 0000") + 1);
  fd = open("./maps/testmap", O_WRONLY);
  write_wall(cr, line, fd);
}
