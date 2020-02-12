/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antman.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:49:50 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 12:49:52 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	init_antgo(int *antgo, int npath, t_path **path, t_stend se)
{
	int i;
	int		shortest;
	int		tants;

	i = -1;
	tants = se.ants;
	while (++i <= npath)
		antgo[i] = path[i]->length;
	while (tants > 0)
	{
		i = 0;
		shortest = 0;
		while (++i <= npath)
			if (antgo[i] < antgo[shortest])
			{
				shortest = i;
				break ;
			}
		antgo[shortest]++;
		tants--;
	}
}

void		antman(t_path **path, int npath, t_stend se, t_ht **ht)
{
	t_path	*tpath;
	int		i;
	int		antgo[npath];

	ft_printf("## ANTMAN ##\nGroup : %d + N of ants : %d\n", npath, se.ants);
	sort_paths(&path, npath);
	init_antgo(antgo, npath, path, se);
	i = -1;
	while (++i <= npath)
	{
		tpath = path[i];
		while (tpath)
		{
			ft_printf("%s > ", tpath->room->room);
			tpath = tpath->next;
		}
		ft_printf("\n[%d,%d,%d]\n", i, path[i]->length, antgo[i] - path[i]->length);
	}
}