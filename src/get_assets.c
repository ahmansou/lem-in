/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:50:57 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 12:50:59 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_assets(t_rooms **rooms, t_lines *l, t_stend *stend)
{
	t_lines *ltmp;

	ltmp = l;
	while (ltmp)
	{
		if (is_comment(ltmp->line))
			ft_putstr("");
		else if ((stend->se = is_stend(ltmp->line)) != 0 || is_room(ltmp->line))
		{
			if (is_stend(ltmp->line) != 0)
			{
				ltmp = ltmp->next;
				if (is_stend(ltmp->line) != 0 || ft_countc(ltmp->line, '-'))
					return (-1);
			}
			if (get_room(rooms, ltmp->line, stend) <= 0)
				return (-2);
		}
		else if (ft_countc(ltmp->line, '-') == 1)
			return (get_links(rooms, ltmp));
		else
			return (0);
		ltmp = ltmp->next;
	}
	return (1);
}

int		get_ants(char *s)
{
	long long int	ant;

	ant = ft_atoi(s);
	if (!is_num(s) || ant < 0)
		return (-7);
	return (ant);
}
