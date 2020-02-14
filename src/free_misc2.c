/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_misc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:03:43 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/13 15:03:45 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free2d(char ***s)
{
	int i;

	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		i++;
	}
	free(*s);
}

void	free_stend(t_stend *se)
{
	ft_strdel(&(*se).start);
	ft_strdel(&(*se).end);
}

void	free_links(t_link **links)
{
	t_link *tlink;
	t_link *tmp;

	tlink = *links;
	while (tlink)
	{
		tmp = tlink->next;
		free(tlink);
		tlink = tmp;
	}
}
