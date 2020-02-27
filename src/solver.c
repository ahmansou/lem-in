/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:53:48 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/27 13:45:13 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	add_element(t_q **q, t_rooms **element)
{
	t_q		*new;
	t_q		*tq;

	if (!(new = (t_q*)malloc(sizeof(t_q))))
		return (0);
	new->element = *element;
	new->next = NULL;
	new->element->visited = 1;
	tq = *q;
	while (tq->next)
		tq = tq->next;
	tq->next = new;
	return (1);
}

static int	is_valid(t_rooms *el, t_link *tlink, t_rooms *tprev, char *start)
{
	if (!ft_strcmp(el->room, start) && tlink->flow > 0 && tprev->visited == 0)
		return (1);
	else if (el->prev && el->prev->cap == 0 && el->cap == 0 &&
			tlink->flow > 0 && tprev->visited == 0)
		return (1);
	else if (el->prev && el->prev->cap == 1 && el->cap == 0 &&
			tlink->flow > 0 && tprev->visited == 0)
		return (1);
	else if (el->prev && el->prev->cap == 1 && el->cap == 1 &&
			tlink->flow > 0 && tprev->visited == 0)
		return (1);
	else if (el->prev && el->prev->cap == 0 && el->cap == 1 &&
			tlink->flow == 2 && tprev->visited == 0)
		return (1);
	return (0);
}

static int	addtoq(t_q **q, t_rooms *element, t_stend se)
{
	t_link	*tlink;
	t_rooms	*tprev;

	tlink = element->links;
	while (tlink)
	{
		tprev = tlink->link;
		if (is_valid(element, tlink, tprev, se.start) > 0)
		{
			if (!add_element(q, &tlink->link))
				return (0);
			tprev->prev = element;
		}
		if (!ft_strcmp(tprev->room, se.end) && tlink->flow > 0)
			return (1);
		tlink = tlink->next;
	}
	return (0);
}

static int	get_q(t_ht ***ht, t_stend se)
{
	t_q		*q;
	t_q		*tq;
	t_ht	*tht;

	if (!(q = (t_q*)malloc(sizeof(t_q))))
		return (0);
	tq = q;
	tht = (*ht)[hash(se.start)];
	while (ft_strcmp(tht->room->room, se.start))
		tht = tht->next;
	q->element = tht->room;
	q->next = NULL;
	tht->room->visited = 1;
	while (tq)
	{
		if (addtoq(&q, tq->element, se))
		{
			free_q(&q);
			return (1);
		}
		tq = tq->next;
	}
	free_q(&q);
	return (0);
}

t_path		***solver(t_rooms *rooms, t_ht ***ht, t_stend se)
{
	t_path	***path;
	int		i[3];

	if (!(path = (t_path***)ft_memalloc(sizeof(t_path**) *
		st_links(*ht, se.start))))
		return (NULL);
	i[0] = 0;
	while (get_q(ht, se) && !(i[2] = 0))
	{
		correction(ht, se);
		if (!(path[i[0]] = (t_path**)ft_memalloc(sizeof(t_path*) * (i[0] + 1))))
			return (NULL);
		while (i[2] <= i[0] && (i[1] = -1))
			path[i[0]][i[2]++] = NULL;
		while (++i[1] <= i[0] && get_path(ht, &path[i[0]][i[1]], se))
			path[i[0]][i[1]]->length = path_size(path[i[0]][i[1]]);
		reset_graph(&rooms);
		i[0]++;
	}
	if (!path[0])
	{
		free(path);
		return (NULL);
	}
	return (path);
}
