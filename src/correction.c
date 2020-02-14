/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:53:48 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/07 19:53:49 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	correct_flow(t_rooms **node, t_rooms **prev)
{
	t_link *tlink;

	tlink = (*node)->links;
	while (tlink && ft_strcmp(tlink->link->room, (*prev)->room))
		tlink = tlink->next;
	tlink->flow++;
	tlink = (*prev)->links;
	while (tlink && ft_strcmp(tlink->link->room, (*node)->room))
		tlink = tlink->next;
	tlink->flow--;
}

void		correction(t_ht ***ht, t_stend se)
{
	t_rooms	*troom;
	t_rooms	*tprev;

	troom = (*ht)[hash(se.end)]->room;
	while (troom && ft_strcmp(troom->room, se.end))
		troom = troom->next;
	tprev = troom;
	while (tprev && ft_strcmp(se.start, tprev->room))
	{
		correct_flow(&tprev, &(tprev->prev));
		tprev->cap = 1;
		tprev = tprev->prev;
	}
}

void		reset_graph(t_rooms **room)
{
	t_rooms	*troom;

	troom = *room;
	while (troom)
	{
		troom->flag = 0;
		troom->visited = 0;
		troom = troom->next;
	}
}
