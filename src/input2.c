/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 20:01:46 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include <fcntl.h>
#include "stdlib.h"
#include "math.h"

static void			calc_inp(t_core *cr, int num, char **v, t_coord *inp)
{
	int			fd;
	char		*line;
	int			j;

	if ((fd = open(SAVEPATH, O_RDONLY)) == -1)
		reopen_10_times(&fd);
	printf(">>>>>>>>>>444>>>>>>>>>>> %d\n", fd);
	j = 0;
	prepare_gnlstr(&cr->gnlstr[1]);
	while (j++ <= num)
	{
		if (gnl_struct(&cr->gnlstr[1], fd, &line) <= 0)
			err_ex(1);
		// printf(">>>>>>>>>>11>>>>>>>>>>> %s\n", line);
		if (j < num + 1)
			free(line);
	}
	v = ft_strsplit(line, ' ');
	free(line);
	inp->x = ft_atof(v[2]) * cr->zoom / UNIT_SIZE;
	inp->y = ft_atof(v[1]) * cr->zoom / UNIT_SIZE;
	ft_arrfree(&v, ft_arrlen(v));
	close(fd);
}

void				process_walls(t_core *cr, char **pts, char **prt, int snum)
{
	t_coord		inp1;
	t_coord		inp2;
	int			i;
	int			num;
	char		**v;

	i = 0;
	while (pts[i + 1])
	{
		num = ft_atoi(pts[i]);
		calc_inp(cr, num, v, &inp1);
		num = ft_atoi(pts[i + 1]);
		calc_inp(cr, num, v, &inp2);
		if (check_dups(cr, inp1, inp2) == 0)
		{
			cr->vs.mem_x = inp1.x;
			cr->vs.mem_y = inp1.y;
			cr->vs.x1 = inp2.x;
			cr->vs.y1 = inp2.y;
			cr->mpsw = ft_atoi(prt[i + 1]) >= 0 ? 1 : cr->mpsw;
			add_wall(cr);
		}
		set_sectors(cr, inp1, inp2, snum);
		i++;
	}
}
