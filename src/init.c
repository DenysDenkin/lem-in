/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:15:08 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/04 17:15:11 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_farm		*init_farm(void)
{
	t_farm *res;

	res = (t_farm *)malloc(sizeof(t_farm));
	res->links = NULL;
	res->occupied = NULL;
	res->paths = NULL;
	res->rooms = NULL;
	res->distribution = NULL;
	res->nrooms = 0;
	res->start = -1;
	res->end = -1;
	res->ants = -1;
	res->info = 0;
	return (res);
}

t_room		**init_rooms(t_farm *farm)
{
	int		i;
	t_room	**res;

	(void)farm;
	res = (t_room **)malloc(sizeof(t_room *) * 25000);
	i = 0;
	while (i < 10000)
	{
		res[i] = (t_room *)malloc(sizeof(t_room));
		res[i]->distance = INF;
		res[i]->name = 0;
		res[i]->next = -1;
		res[i]->x = 0;
		res[i++]->y = 0;
	}
	return (res);
}

int			*init_ants(t_farm *farm, int start)
{
	int		*res;
	int		i;

	res = (int *)malloc(sizeof(int) * farm->ants);
	i = 0;
	while (i < farm->ants)
		res[i++] = start;
	return (res);
}

int			*init_occupied(t_farm *farm)
{
	int		*res;
	int		i;

	res = (int *)malloc(sizeof(int) * farm->nrooms);
	i = 0;
	while (i < farm->nrooms)
		res[i++] = 0;
	return (res);
}

int			**init_links(t_farm *farm)
{
	int		i;
	int		j;
	int		**res;

	res = (int **)malloc(sizeof(int *) * farm->nrooms);
	i = 0;
	while (i < farm->nrooms)
	{
		res[i] = (int *)malloc(sizeof(int) * farm->nrooms);
		j = 0;
		while (j < farm->nrooms)
			res[i][j++] = 0;
		i++;
	}
	return (res);
}
