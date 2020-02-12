/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:09:27 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/31 13:09:29 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	add_link(t_rooms **current, t_rooms **room, char *link)
{
	t_rooms *rtmp;
	t_link *tmp;
	t_link	*new;

	rtmp = *room;
	while (rtmp && ft_strcmp(rtmp->room, link))
		rtmp = rtmp->next;
	if (!rtmp)
		return (0);
	if (!(new = (t_link*)malloc(sizeof(t_link))))
		return (0);
	new->link = rtmp;
	new->flow = 1;
	tmp = (*current)->links;
	new->next = tmp;
	(*current)->links = new;
	return (1);
}

static int	get_link(t_rooms **rooms, char *line)
{
	char	**split;
	int		done;
	t_rooms	*rtmp;

	rtmp = *rooms;
	split = ft_strsplit(line, '-');
	done = 0;
	if (!split[0] || !split[1])
		return (-6);
	if (!ft_strcmp(split[1], split[0]))
		return (-5);
	while (rtmp)
	{
		if (!ft_strcmp(rtmp->room, split[0]))
			done += add_link(&rtmp, rooms, split[1]);
		if (!ft_strcmp(rtmp->room, split[1]))
			done += add_link(&rtmp, rooms, split[0]);
		rtmp = rtmp->next;
	}
	if (done != 2)
		return (-4);
	return (1);
}

int			get_links(t_rooms **rooms, t_lines *lines)
{
	t_rooms	*rtmp;
	char	**split;
	int		error;

	while (lines)
	{
		if (is_comment(lines->line))
			ft_putstr("");
		else if (ft_countc(lines->line, '-') == 1 &&
				(error = get_link(rooms, lines->line)))
		{
			if (error <= 0)
				return (error);
		}
		else
			return (-6);
		lines = lines->next;
	}
	return (1);
}