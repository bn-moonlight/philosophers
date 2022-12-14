/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkaya <sakkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:11 by sakkaya           #+#    #+#             */
/*   Updated: 2022/12/14 12:53:21 by sakkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *s)
{
	int	a;
	int	c;

	a = 0;
	c = 0;
	while (s[a])
	{
		if (s[a] >= '0' && s[a] <= '9')
			a++;
		else
		{
			printf(RED"Wrong arguments.\n"RESET);
			return (-1);
		}
	}
	a = 0;
	while (s[a] <= 32)
		a++;
	while (s[a] >= '0' && s[a] <= '9')
		c = c * 10 + (s[a++] - '0');
	return (c);
}

uint64_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	printthreadm(int id, char *s, t_philos *stk)
{
	if (stk->dead == 0)
	{
		pthread_mutex_lock(&stk->random);
		printf(GREEN"%llu " RESET, gettime() - stk->start_time);
		printf(BLACK"%d %s"RESET, id, s);
		pthread_mutex_unlock(&stk->random);
	}
}

void	passtime(int time, t_list *stk)
{
	uint64_t	start;

	start = gettime();
	while (stk->s_stk->dead == 0)
	{
		if (gettime() - start >= time)
			break ;
		usleep(10);
	}
}

int	line_25(char	**av)
{
	if (ft_atoi(av[1]) <= 1)
	{
		printf(BLUE"0 0 Dead."RESET);
		return (0);
	}
	return (1);
}
