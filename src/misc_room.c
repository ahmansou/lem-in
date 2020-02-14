/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:20:59 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 14:21:00 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_rooms(t_rooms **rooms)
{
	t_rooms *tmp;
	t_rooms *troom;

	tmp = *rooms;
	while (tmp)
	{
		troom = tmp->next;
		ft_strdel(&tmp->room);
		free_links(&(tmp->links));
		free(tmp);
		tmp = troom;
	}
}

int		st_end(char *room, t_stend *stend, int se)
{
	if (se == 1)
		stend->start = ft_strdup(room);
	if (se == 2)
		stend->end = ft_strdup(room);
	return (0);
}
