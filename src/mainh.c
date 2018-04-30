/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:04:36 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/08 19:04:37 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void				minimize_distances(t_farm *farm, int room)
{
	int			i;

	i = 0;
	if (room == -1)
		room = farm->end;
	while (i < farm->nrooms)
	{
		if (farm->links[room][i] == 1)
		{
			if (farm->rooms[i]->distance > farm->rooms[room]->distance + 1)
			{
				farm->rooms[i]->distance = farm->rooms[room]->distance + 1;
				minimize_distances(farm, i);
			}
		}
		i++;
	}
}

void				recount_distances(t_farm *farm, int *dist, int room)
{
	int			i;

	i = 0;
	if (room == -1)
		room = farm->end;
	while (i < farm->nrooms)
	{
		if (farm->links[room][i] == 1)
		{
			if (dist[i] > dist[room] + 1 && farm->rooms[i]->next == -1)
			{
				dist[i] = dist[room] + 1;
				recount_distances(farm, dist, i);
			}
		}
		i++;
	}
}

void				optimize_positions(t_farm *farm, int *ants, int first)
{
	t_iter		it;

	it.i = -1;
	while (++it.i < farm->ants)
		if (ants[it.i] == farm->start && (it.k = -1))
		{
			while (++it.k < farm->paths->cursize)
				if (farm->distribution[it.k] > 0 && (farm->occupied[farm->\
	paths->path[it.k][1]] == 0 || farm->paths->path[it.k][1] == farm->end))
				{
					farm->occupied[ants[it.i]]--;
					farm->distribution[it.k]--;
					ants[it.i] = farm->paths->path[it.k][1];
					farm->occupied[ants[it.i]]++;
					print_ant(farm, it.i, ants, first++);
					break ;
				}
		}
		else if (ants[it.i] != farm->end)
		{
			farm->occupied[ants[it.i]]--;
			ants[it.i] = farm->rooms[ants[it.i]]->next;
			farm->occupied[ants[it.i]]++;
			print_ant(farm, it.i, ants, first++);
		}
}

void				lemmings(t_farm *farm)
{
	t_iter		it;
	int			*ants;
	int			first;

	ants = init_ants(farm, farm->start);
	farm->occupied = init_occupied(farm);
	farm->occupied[farm->start] = farm->ants;
	while (farm->occupied[farm->end] != farm->ants)
	{
		it.i = -1;
		first = 0;
		optimize_positions(farm, ants, first);
		write(1, "\n", 1);
	}
	free(ants);
}

int					*copy_distances(t_farm *farm)
{
	int		*res;
	int		i;

	res = (int *)malloc(sizeof(int) * farm->nrooms);
	i = -1;
	while (++i < farm->nrooms)
		res[i] = farm->rooms[i]->distance;
	return (res);
}
