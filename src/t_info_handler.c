/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:15:02 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/04 17:15:06 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_info			*init_info(void)
{
	t_info		*res;

	res = (t_info *)malloc(sizeof(t_info));
	res->cursize = 0;
	res->maxsize = 2;
	res->tab = (char **)malloc(sizeof(char *) * (res->maxsize + 1));
	res->tab[res->maxsize] = 0;
	return (res);
}

void			add_info(t_info *info, char *line)
{
	int		i;
	char	**newtab;

	if (info->cursize >= info->maxsize)
	{
		newtab = (char **)malloc(sizeof(char *) * (info->maxsize * 2 + 1));
		i = -1;
		while (++i < info->maxsize)
			newtab[i] = info->tab[i];
		free(info->tab);
		info->tab = newtab;
		info->maxsize *= 2;
		info->tab[info->maxsize] = 0;
	}
	info->tab[info->cursize] = line;
	info->cursize++;
}

int				nameok(char *line, t_info *roomnames, int amount)
{
	char		**tab;
	int			i;
	int			ok;

	i = -1;
	ok = 0;
	tab = (amount == 1) ? ft_strsplit(line, ' ') : ft_strsplit(line, '-');
	if (ft_strchr(tab[0], '-') != NULL)
		return (0 + freetabn((void ***)&tab, -1));
	while (amount == 1 && ++i < roomnames->cursize)
	{
		if (tab[0][0] == 'L' || ft_strcmp(tab[0], roomnames->tab[i]) == 0)
			return (0 + freetabn((void ***)&tab, -1));
	}
	while (amount == 2 && ++i < roomnames->cursize)
	{
		(ft_strcmp(roomnames->tab[i], tab[0]) == 0) ? ok++ : 1;
		(ft_strcmp(roomnames->tab[i], tab[1]) == 0) ? ok++ : 1;
		if (tab[0][0] == 'L' || tab[1][0] == 'L' ||
				(i == roomnames->cursize - 1 && ok != 2))
			return (0 + freetabn((void ***)&tab, -1));
	}
	return (1 + freetabn((void ***)&tab, -1));
}

int				is_valid_line(t_farm *farm, char *line)
{
	static int		stage = 0;
	static t_info	*roomnames = NULL;

	(!roomnames) ? roomnames = init_info() : roomnames;
	(count_words(line, ' ') != 3 && count_words(line, '-')\
									== 2 && stage == 1) ? stage++ : 1;
	if (line[0] == '#')
		return (1);
	if (stage == 0)
	{
		stage++;
		return (ft_isnumber(line) && ft_atoi(line) > 0);
	}
	else if (stage == 1)
	{
		if (count_words(line, ' ') != 3 || nameok(line, roomnames, 1) != 1)
			return (0);
		else
			farm->nrooms++;
	}
	else if (stage == 2)
		return (!(count_words(line, '-') != 2 ||\
					nameok(line, roomnames, 2) != 1));
		return (1);
}

int				room_n(const char *room, t_farm *farm)
{
	int		i;

	i = 0;
	while (i < farm->nrooms && farm->rooms[i] && farm->rooms[i]->name)
	{
		if (ft_strcmp(room, farm->rooms[i]->name) == 0)
			return (i);
		i++;
	}
	return (-1);
}
