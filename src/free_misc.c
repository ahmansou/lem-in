/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:09:43 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/13 14:09:44 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_lines(t_lines **lines)
{
	t_lines *tmp;
	t_lines *tline;

	tmp = *lines;
	while (tmp)
	{
		tline = tmp->next;
		ft_strdel(&tmp->line);
		free(tmp);
		tmp = tline;
	}
}

void	free_q(t_q **q)
{
	t_q	*tq;
	t_q	*tqq;

	tq = *q;
	while (tq)
	{
		tqq = tq->next;
		free(tq);
		tq = tqq;
	}
}

void	free_spath(t_path ***spath, int npath)
{
	int		i;

	i = 0;
	while (i <= npath)
	{
		free((*spath)[i]);
		i++;
	}
	free(*spath);
}

void	free_paths(t_path ****path, int links)
{
	t_path	*tpath;
	t_path	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < links && !(j = 0))
		if ((*path)[i])
		{
			while (j <= i)
			{
				tpath = (*path)[i][j];
				while (tpath)
				{
					tmp = tpath->next;
					free(tpath);
					tpath = tmp;
				}
				j++;
			}
			free((*path)[i]);
		}
	free(*path);
}

void	free_ht(t_ht ***ht)
{
	t_ht	*tht;
	t_ht	*tmp;
	int		i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tht = (*ht)[i];
		while (tht)
		{
			tmp = tht->next;
			free(tht);
			tht = tmp;
		}
		i++;
	}
	free(*ht);
}
