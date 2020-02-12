/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:53:48 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/07 19:53:49 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		st_links(t_ht **ht, char *st)
{
	t_rooms *start;

	start = ht[hash(st)]->room;
	while (start && ft_strcmp(start->room, st))
		start = start->next;
	return (num_links(start));
}

int		git_scores(t_path ***path, int stlink, t_stend se)
{
	t_score_env	env;
	int			score[stlink];

	env.i = -1;
	env.best_score[0] = 2147483647;
	while (++env.i < stlink && (env.j = -1))
	{
		if (!(env.nrooms = 0) && !path[env.i])
			continue ;
		while (++env.j <= env.i)
		{
			env.tpath = path[env.i][env.j];
			while (env.tpath && ft_strcmp(se.end, env.tpath->room->room))
				env.tpath = 0 * env.nrooms++ + env.tpath->next;
		}
		score[env.i] = ((se.ants + env.nrooms) % env.j == 0) ?
			(se.ants + env.nrooms) / env.j : (se.ants + env.nrooms) / env.j + 1;
		env.best_score[1] = (score[env.i] < env.best_score[0]) ?
			env.i : env.best_score[1];
		env.best_score[0] = (score[env.i] < env.best_score[0]) ?
			score[env.i] : env.best_score[0];
	}
	return (env.best_score[1]);
}