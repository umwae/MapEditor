/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/14 20:58:32 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <fcntl.h>

void		name_sec_list(t_core *cr)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec)
	{
		printf("%d ", sec->id);
		sec = sec->next;
	}
	printf("\n");
}

void		add_sec_list(t_core *cr)
{
	t_sec	*sec;

	sec = (t_sec *)malloc(sizeof(t_sec));
	sec->next = *cr->slist;
	sec->illum = 0.75;
	sec->floor = ST_FLOOR_HIGHT;
	sec->ceiling = ST_CEIL_HIGHT;
	sec->id = cr->sec_num - 1;
	*cr->slist = sec;
}

void				sec_list_id_replace(t_core *cr, int new, int old)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec->next && sec->id != old)
		sec = sec->next;
	sec->id = new;
}

void		del_sec_list(t_core *cr, int idref)
{
	t_sec	*pr;
	t_sec	*sec;

	pr = *cr->slist;
	if (!pr)
		return ;
	if (pr->id == idref)
	{
		*cr->slist = pr->next;
		free(pr);
		return ;
	}
	while (pr)
	{
		if (!pr->next)
		{
			return ;
		}
		sec = pr->next;
		if (!sec)
			return ;
		if (sec->id == idref)
		{
			pr->next = sec->next;
			free(sec);
			return ;
		}
		pr = pr->next;
	}
}

t_sec				*find_sec_list(t_core *cr, int idref)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec)
	{
		if (sec->id == idref)
			break ;
		sec = sec->next;
	}
	return (sec);
}

// void			record_textures(t_core *cr, int fd)
// {
// 	char	*text;
// 	t_sec	*sec;
//
// 	text = ft_strnew(100);
// 	sec = *cr->slist;
// 	ft_putstr_fd("\n", fd);
// 	while (sec)
// 	{
// 		text = ft_strnew(100);
// 		ft_strcat(text, "o|");
// 		ft_strcat(text, ft_itoa(sec->sec));
// 		ft_strcat(text, "|");
// 		ft_strcat(text, ft_ftoa(sec->fcoord.y / cr->zoom * UNIT_SIZE));
// 		ft_strcat(text, " ");
// 		ft_strcat(text, ft_ftoa(sec->fcoord.x / cr->zoom * UNIT_SIZE));
// 		ft_strcat(text, "|");
// 		ft_strcat(text, ft_itoa(sec->type));
// 		ft_strcat(text, "|\n");
// 		ft_putstr_fd(text, fd);
// 		sec = sec->next;
// 	}
// 	free(text);
// }
