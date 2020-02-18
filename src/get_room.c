/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:57:55 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 13:57:55 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	add_room(t_rooms **rooms, char *line)
{
	t_rooms	*new;
	t_rooms *tmp;

	new = (t_rooms*)malloc(sizeof(t_rooms));
	new->room = ft_strdup(line);
	new->cap = 0;
	new->flag = 0;
	new->links = NULL;
	new->prev = NULL;
	new->visited = 0;
	tmp = *rooms;
	new->next = tmp;
	*rooms = new;
}

int			get_room(t_rooms **rooms, char *line, t_stend *stend)
{
	char	**split;

	if (line[0] == 'L' || line[0] == '#')
		return (-1);
	split = ft_strsplit(line, ' ');
	if (!split[0] || !split[1] || !split[2] ||
		!is_num(split[1]) || !is_num(split[2]))
	{
		free2d(&split);
		return (0);
	}
	if (stend->se == 1 && !stend->start)
		st_end(split[0], stend, 1);
	else if (stend->se == 2 && !stend->end)
		st_end(split[0], stend, 2);
	else if (stend->se > 0 && (stend->start || stend->end))
	{
		free2d(&split);
		return (0);
	}
	add_room(rooms, split[0]);
	free2d(&split);
	return (1);
}
