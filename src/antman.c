/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antman.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:49:50 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/27 15:09:46 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	init_antgo(int *antgo, int npath, t_path **path, t_stend se)
{
	int	i;
	int	shortest;
	int	tants;

	i = -1;
	tants = se.ants;
	while (++i <= npath)
	{
		if (!path[i])
			continue ;
		antgo[i] = path[i]->length;
	}
	while (tants > 0)
	{
		i = 0;
		shortest = 0;
		while (++i <= npath)
			if (path[i] && antgo[i] < antgo[shortest])
			{
				shortest = i;
				break ;
			}
		antgo[shortest]++;
		tants--;
	}
}

static int	*init_antstart(int npath, int *antgo, t_path **path)
{
	int		i;
	int		*antstart;

	if (!(antstart = (int*)malloc(sizeof(int) * npath + 1)))
		return (NULL);
	antstart[0] = 0;
	antgo[0] -= path[0]->length;
	i = 0;
	while (++i <= npath)
	{
		if (!path[i])
			continue ;
		antgo[i] -= path[i]->length;
		if (antgo[i] > 0)
			antstart[i] = antstart[i - 1] + antgo[i - 1];
		else
			antstart[i] = -1;
	}
	return (antstart);
}

static void	init_ants(t_ant_env antenv, int npath)
{
	int i;
	int j;

	i = 0;
	while (i <= npath)
	{
		j = antenv.antstart[i];
		while (j < antenv.antstart[i] + antenv.antgo[i])
		{
			antenv.ants[j].pathid = i;
			antenv.ants[j].arrived = 0;
			antenv.ants[j].croom = antenv.spath[i];
			j++;
		}
		i++;
	}
}

static void	putants(t_ant_env env, t_stend se)
{
	int i;

	while (!allin(env, se.ants) && (i = -1))
	{
		while (++i < se.ants)
		{
			if (env.ants[i].arrived == 0)
				if (env.ants[i].croom->next &&
				env.ants[i].croom->next->busy == 0)
				{
					env.ants[i].croom->busy = 0;
					env.ants[i].croom = env.ants[i].croom->next;
					if (ft_strcmp(env.ants[i].croom->room->room, se.end))
						env.ants[i].croom->busy = 1;
					ft_printf("L%d-%s ", i + 1,
							env.ants[i].croom->room->room);
					if (!ft_strcmp(env.ants[i].croom->room->room, se.end))
						env.ants[i].arrived = 1;
				}
		}
		ft_putendl("");
	}
}

int			antman(t_path **path, int npath, t_stend se, t_lines *lines)
{
	t_ant_env	ant_env;

	if (!(ant_env.ants = (t_ants*)malloc(sizeof(t_ants) * se.ants)))
		return (0);
	if (!(ant_env.spath = (t_path**)malloc(sizeof(t_path*) * (npath + 1))))
		return (0);
	if (!(ant_env.antgo = (int*)malloc(sizeof(int) * (npath + 1))))
		return (0);
	sort_paths(&path, npath);
	if (!init_paths(&path, npath, ant_env.spath))
		return (0);
	init_antgo(ant_env.antgo, npath, path, se);
	if (!(ant_env.antstart = init_antstart(npath, ant_env.antgo, path)))
		return (0);
	init_ants(ant_env, npath);
	print_lines(lines);
	putants(ant_env, se);
	free(ant_env.ants);
	free(ant_env.antgo);
	free_spath(&ant_env.spath, npath);
	free(ant_env.antstart);
	return (1);
}
