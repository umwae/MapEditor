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

int					find_msg_by_id(t_core *cr, int id)
{
	t_list	*curr;

	curr = *cr->messages;
	while (curr)
	{
		if (((t_msg *)curr->content)->id == id)
			return (1);
		curr = curr->next;
	}
	return (0);
}

void				show_messages(t_core *cr)
{
	t_list	*curr;
	t_msg		*msg;

	if (!*cr->messages)
		return ;
	curr = *cr->messages;
	msg = (t_msg *)curr->content;
	while (curr)
	{
		mlx_string_put(cr->mlx, cr->win, msg->pos.x, \
		msg->pos.y, msg->color, \
		*msg->text);
		curr = curr->next;
	}
}

void		add_message(t_core *cr, char **text, int pos, int color, int id)
{
	t_msg		*msg;
	t_list	*list;

	msg = (t_msg *)malloc(sizeof(t_msg));
	if (pos == 2)
	{
		msg->pos.x = WIN_WIDTH / 2;
		msg->pos.y = WIN_HIGHT * 0.03;
	}
	msg->text = text;
	msg->color = color;
	msg->id = id;
	list = ft_lstnew(msg, sizeof(t_msg));
	ft_lstadd(cr->messages, list);
	//
	list = *cr->messages;
	while (list)
	{
		printf("JJJ\n");
		list = list->next;
	}
}
