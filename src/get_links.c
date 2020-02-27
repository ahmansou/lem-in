/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:09:27 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/27 13:42:42 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	add_link(t_rooms **current, t_rooms **room, char *link)
{
	t_rooms	*rtmp;
	t_link	*tmp;
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

static int	return_err(char ***split, int err)
{
	free2d(split);
	return (err);
}

static int	get_link(t_rooms **rooms, char *line)
{
	char	**spl;
	int		done;
	t_rooms	*rtmp;

	rtmp = *rooms;
	spl = ft_strsplit(line, '-');
	if (!(done = 0) && (!spl[0] || !spl[1] || !ft_strcmp(spl[1], spl[0])))
		return (return_err(&spl, -6));
	while (rtmp)
	{
		if (!ft_strcmp(rtmp->room, spl[0]))
			done += add_link(&rtmp, rooms, spl[1]);
		if (!ft_strcmp(rtmp->room, spl[1]))
			done += add_link(&rtmp, rooms, spl[0]);
		rtmp = rtmp->next;
	}
	if (done != 2)
		return (return_err(&spl, -4));
	free2d(&spl);
	return (1);
}

int			get_links(t_rooms **rooms, t_lines *lines)
{
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
