/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:01:48 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 14:01:49 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				is_num(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

unsigned int	hash(const char *name)
{
	unsigned int	hash;
	size_t			i;
	size_t			name_len;

	hash = 0;
	i = 0;
	name_len = ft_strlen(name);
	while (i < name_len)
	{
		hash = hash * 63 + name[i];
		i++;
	}
	hash = hash % TABLE_SIZE;
	return (hash);
}

int				num_links(t_rooms *room)
{
	t_link	*tlink;
	int		i;

	i = 0;
	tlink = room->links;
	while (tlink)
	{
		i++;
		tlink = tlink->next;
	}
	return (i);
}

int				path_size(t_path *path)
{
	int		c;
	t_path	*tpath;

	c = 0;
	tpath = path;
	while (tpath)
	{
		c++;
		tpath = tpath->next;
	}
	return (--c);
}

int				allin(t_ant_env antenv, int ant)
{
	int i;

	i = 0;
	while (i < ant)
	{
		if (antenv.ants[i].arrived == 0)
			return (0);
		i++;
	}
	return (1);
}
