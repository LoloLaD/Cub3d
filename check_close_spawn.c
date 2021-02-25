/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:13:52 by lfourmau          #+#    #+#             */
/*   Updated: 2021/02/25 08:38:22 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int valid_extrem_lines(map_struct *ms)
{
	int i;
	int nb_splits;

	i = 0;
	nb_splits = number_of_split(ms->map);
	while (ms->map[0][i] && (ms->map[0][i] == ' ' || ms->map[0][i] == '1'))
		i++;
	if (ms->map[0][i] != 0)
		return (1);
	i = 0;
	while (ms->map[nb_splits - 1][i] && (ms->map[nb_splits - 1][i] == ' ' || ms->map[nb_splits - 1][i] == '1'))
		i++;
	if (ms->map[nb_splits - 1][i] != 0)
		return (1);
	return (0);
}

int valid_middle_lines(map_struct *ms)
{
	int i;
	int j;
	int nb_splits;

	i = 1;
	nb_splits = number_of_split(ms->map);
	while (i < nb_splits - 1) //i - 1 car extremites deja check
	{
		j = 0;
		while (ft_isspace(ms->map[i][j]))
			j++;
		if (ms->map[i][j] != '1')
			return (1);
		while (ms->map[i][j])
			j++;
		j--;
		while (ft_isspace(ms->map[i][j]))
			j--;
		if (ms->map[i][j] != '1')
			return (1);
		i++;
	}
	return (0);
}

int check_spawns(char c, map_struct *ms)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (ms->nb_spawns == 0)
		{
			ms->spawn = c;
			ms->nb_spawns += 1;
		}
		else
			return (1);
	}
	return (0);
}

int check_zeros(map_struct *ms)
{
	int i;
	int j;

	i = 0;
	while (ms->map[i])
	{
		j = 0;
		while (ms->map[i][j])
		{
			if (ms->map[i][j] == '0')
			{
				if (ms->map[i - 1][j] == ' ')
					return (1);
				if (ms->map[i][j - 1] == ' ')
					return (1);
				if (ms->map[i + 1][j] == ' ')
					return (1);
				if (ms->map[i][j + 1] == ' ')
					return (1);
			}
			else if (check_spawns(ms->map[i][j], ms))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_spawn_close(map_struct *ms)
{
	if (valid_extrem_lines(ms))
		return (1);
	if (valid_middle_lines(ms))
		return (1);
	if(check_zeros(ms))
		return (1);
	if (ms->nb_spawns == 0)
		return (1);
	return (0);
}