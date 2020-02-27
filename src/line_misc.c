/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:41:57 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 13:41:58 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	is_comment(char *s)
{
	if (s && s[0] == '#' && ft_strcmp(s, "##start") && ft_strcmp(s, "##end"))
		return (1);
	return (0);
}

int	is_room(char *s)
{
	if (ft_countc(s, ' ') == 2)
		return (1);
	return (0);
}

int	is_stend(char *s)
{
	if (s)
	{
		if (!ft_strcmp(s, "##start"))
			return (1);
		if (!ft_strcmp(s, "##end"))
			return (2);
	}
	return (0);
}
