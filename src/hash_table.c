/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:34:40 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/27 13:27:42 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	add_to_ht(t_ht **ht, t_rooms *room)
{
	t_ht			*nht;
	t_ht			*tht;

	if (!(nht = (t_ht*)malloc(sizeof(t_ht))))
		return (0);
	nht->room = room;
	nht->next = NULL;
	if (!(*ht))
		*ht = nht;
	else
	{
		tht = (*ht);
		while (tht->next)
			tht = tht->next;
		tht->next = nht;
	}
	return (1);
}

static int	init_ht(t_ht ***ht, t_rooms *room)
{
	t_rooms			*troom;
	unsigned int	hsh;

	troom = room;
	while (troom)
	{
		hsh = hash(troom->room);
		if (!add_to_ht(&(*ht)[hsh], troom))
			return (0);
		troom = troom->next;
	}
	return (1);
}

t_ht		**create_ht(t_rooms *room)
{
	int		i;
	t_ht	**ht;

	i = 0;
	if (!(ht = (t_ht**)malloc(sizeof(t_ht*) * TABLE_SIZE)))
		return (NULL);
	while (i < TABLE_SIZE)
		ht[i++] = NULL;
	if (!init_ht(&ht, room))
		return (NULL);
	return (ht);
}
