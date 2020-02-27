/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:53:48 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/27 13:45:42 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	addtopath(t_path **path, t_rooms *room)
{
	t_path	*npath;
	t_path	*tpath;

	if (!(npath = (t_path*)malloc(sizeof(t_path))))
		return (0);
	npath->room = room;
	npath->busy = 0;
	npath->next = NULL;
	if (!(*path))
		*path = npath;
	else
	{
		tpath = *path;
		while (tpath->next)
			tpath = tpath->next;
		tpath->next = npath;
	}
	return (1);
}

t_rooms		*get_start(t_ht **ht, char *start)
{
	t_rooms	*troom;

	troom = ht[hash(start)]->room;
	while (ft_strcmp(troom->room, start))
		troom = troom->next;
	return (troom);
}

int			get_path(t_ht ***ht, t_path **path, t_stend se)
{
	t_rooms	*troom;
	t_link	*tlink;

	troom = get_start(*ht, se.start);
	while (troom && ft_strcmp(troom->room, se.end))
	{
		tlink = troom->links;
		while (tlink)
		{
			if (tlink->flow == 0 && tlink->link->flag == 0)
			{
				addtopath(path, tlink->link);
				if (ft_strcmp(tlink->link->room, se.end))
					tlink->link->flag = 1;
				troom = tlink->link;
				break ;
			}
			tlink = tlink->next;
		}
		if (!tlink)
			return (0);
	}
	if (!troom)
		return (0);
	return (1);
}

void		sort_paths(t_path ***path, int npath)
{
	t_path	**tpath;
	t_path	*tempp;
	int		i;
	int		j;

	i = -1;
	tpath = *path;
	while (++i <= npath)
	{
		j = i;
		while (++j <= npath)
			if (tpath[j] && path_size(tpath[i]) > path_size(tpath[j]))
			{
				tempp = tpath[j];
				tpath[j] = tpath[i];
				tpath[i] = tempp;
			}
	}
}

int			init_paths(t_path ***path, int npath, t_path **spath)
{
	t_path	*tpath;
	int		i;

	i = -1;
	while (++i <= npath)
	{
		tpath = (*path)[i];
		while (tpath->next)
			tpath = tpath->next;
	}
	i = -1;
	while (++i <= npath)
	{
		if (!(spath[i] = (t_path*)malloc(sizeof(t_path))))
			return (0);
		spath[i]->next = (*path)[i];
		tpath = (*path)[i];
		while (tpath)
		{
			tpath->busy = 0;
			tpath = tpath->next;
		}
	}
	return (1);
}
