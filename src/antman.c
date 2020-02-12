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

static int	init_antgo(int *antgo, int npath, t_path **path, t_stend se)
{
	int i;
	int		shortest;
	int		tants;

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
	ft_printf("pa");
	return (1);
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
		while (j <antenv.antstart[i] + antenv.antgo[i])
		{
			antenv.ants[j].pathid = i;
			antenv.ants[j].arrived = 0;
			antenv.ants[j].croom = antenv.spath[i];
			j++;
		}
		i++;
	}
	
}

int			allin(t_ant_env antenv, int ant)
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

void		putants(t_path **path, int npath, t_ant_env antenv, t_stend se)
{
	int i;
	int j;

	while (!allin(antenv, se.ants) && (i = -1))
	{
		while (++i <= npath)
		{
			if (antenv.antgo[i] <= 0)
				continue ;
			j = antenv.antstart[i] - 1;
			while (++j < antenv.antstart[i] + antenv.antgo[i])
				if (antenv.ants[j].arrived == 0)
					if (antenv.ants[j].croom->next &&
						antenv.ants[j].croom->next->busy == 0)
					{
						antenv.ants[j].croom->busy = 0;
						antenv.ants[j].croom = antenv.ants[j].croom->next;
						if (ft_strcmp(antenv.ants[j].croom->room->room, se.end))
							antenv.ants[j].croom->busy = 1;
						ft_printf("L%d-%s ", j + 1, antenv.ants[j].croom->room->room);
						if (!ft_strcmp(antenv.ants[j].croom->room->room, se.end))
							antenv.ants[j].arrived = 1;
					}
		}
		ft_printf(" %d ", allin(antenv, se.ants));
		ft_putendl("");
	}
}

int			antman(t_path **path, int npath, t_stend se, t_ht **ht)
{
	t_ant_env	ant_env;
	
	if (!(ant_env.ants = (t_ants*)malloc(sizeof(t_ants) * se.ants)))
		return (0);
	if (!(ant_env.spath = (t_path**)malloc(sizeof(t_path*) * (npath + 1))))
		return (0);
	if (!(ant_env.antgo = (int*)malloc(sizeof(int) * (npath + 1))))
		return (0);
	ant_env.ants[se.ants - 1].arrived = 1;
	ft_printf("## ANTMAN ##\nGroup : %d + N of ants : %d\n", npath, se.ants);
	sort_paths(&path, npath);
	if (!init_paths(&path, npath, ant_env.spath))
		return (0);
	ft_printf("d");
	if (!init_antgo(ant_env.antgo, npath, path, se))
		return (0);
	if (!(ant_env.antstart = init_antstart(npath, ant_env.antgo, path)))
		return (0);
	ft_printf("la");
	init_ants(ant_env, npath);
	
	
	t_path	*tpath;
	int		i;
	i = -1;
	while (++i <= npath)
	{
		// ft_printf("%s : ", ant_env.spath[i]->next->room->room);
		// if (!path[i])
		// 	continue ;
		tpath = path[i];
		// ft_printf("\n[%d] ", i);
		while (tpath)
		{
			ft_printf("%s > ", tpath->room->room);
			// ft_printf("{%s, %d} > ", tpath->room->room, tpath->busy);
			tpath = tpath->next;
		}
		ft_printf("\n[%d, %d,%d, %d]\n",
		i, ant_env.antstart[i], ant_env.antstart[i] + ant_env.antgo[i] - 1, ant_env.antgo[i]);
	}
	ft_putendl("\n----------------\n");


	putants(path, npath, ant_env, se);
	
	
	


	return (1);
}