/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:14:56 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/16 15:43:18 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				find_path(t_farm *farm, int *route, int *dists_copy, \
															t_iter *it)
{
	int		minr;
	int		min;

	minr = -1;
	it->j = 0;
	min = dists_copy[route[it->i - 1]];
	while (it->j < farm->nrooms)
	{
		if (farm->links[route[it->i - 1]][it->j] == 1 \
		&& dists_copy[it->j] < min && (farm->rooms[it->j]->next == -1 \
										|| farm->end == it->j))
		{
			min = dists_copy[it->j];
			minr = it->j;
		}
		it->j++;
	}
	if (minr == -1)
		return ;
	route[it->i] = minr;
	farm->links[minr][route[it->i - 1]] = 0;
	farm->links[route[it->i - 1]][minr] = 0;
	(route[it->i - 1] != farm->start) ? \
					farm->rooms[route[it->i - 1]]->next = minr : 1;
	it->i++;
}

void				find_paths(t_farm *farm)
{
	int		*route;
	t_iter	it;
	int		*dists_copy;

	farm->paths = init_paths();
	dists_copy = copy_distances(farm);
	while (dists_copy[farm->start] != INF)
	{
		route = (int *)malloc(sizeof(int) * farm->nrooms);
		route[0] = farm->start;
		it.i = 1;
		while (route[it.i - 1] != farm->end && dists_copy[farm->start] != INF)
			find_path(farm, route, dists_copy, &it);
		add_path(farm->paths, route);
		if (route[1] == farm->end)
			return (free(dists_copy));
		it.k = -1;
		while (++it.k < farm->nrooms)
			dists_copy[it.k] = (it.k != farm->end) ? INF : 0;
		recount_distances(farm, dists_copy, -1);
	}
	free(dists_copy);
}

int					pathlen(t_farm *farm, int *path)
{
	int		res;

	res = 0;
	while (path[res] != farm->end)
		res++;
	return (res);
}

void				distribute(t_farm *farm)
{
	int				lengths[farm->paths->cursize];
	int				i;
	int				sum;
	double			avg;

	farm->distribution = (int *)malloc(sizeof(int) * farm->paths->cursize);
	i = -1;
	while (++i < farm->paths->cursize)
		lengths[i] = pathlen(farm, farm->paths->path[i]);
	i = -1;
	sum = farm->ants;
	while (++i < farm->paths->cursize)
		sum += lengths[i];
	i = -1;
	avg = (double)sum / farm->paths->cursize;
	sum = farm->ants;
	while (++i < farm->paths->cursize - 1)
	{
		farm->distribution[i] = (ft_round(avg)) - lengths[i];
		sum -= farm->distribution[i];
	}
	farm->distribution[farm->paths->cursize - 1] = sum;
}

int					main(void)
{
	t_farm	*farm;

	farm = init_farm();
	if (parse_input(farm) < 0)
		return (-1);
	if (farm->end == -1 || farm->start == -1)
		return (nerror("No start or end"));
	farm->rooms[farm->end]->distance = 0;
	!(farm->links) ? farm->links = init_links(farm) : NULL;
	minimize_distances(farm, -1);
	find_paths(farm);
	if (farm->paths->cursize == 0)
		return (nerror("No solution"));
	drop_out(farm);
	distribute(farm);
	lemmings(farm);
	return (0);
}
