/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkaya <sakkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:05 by sakkaya           #+#    #+#             */
/*   Updated: 2022/12/14 12:32:06 by sakkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	starteating(t_list *free)
{
	pthread_mutex_lock(&free->s_stk->fork_mutex[free->l_forkid]);
	printthreadm(free->id, BLUE"has taken the left fork\n"RESET, free->s_stk);
	pthread_mutex_lock(&free->s_stk->fork_mutex[free->r_forkid]);
	printthreadm(free->id, BLUE"has taken the right fork\n"RESET, free->s_stk);
	printthreadm(free->id, PINK"is eating\n"RESET, free->s_stk);
	free->last_eat = gettime();
	passtime(free->s_stk->time_to_eat, free);
	pthread_mutex_unlock(&free->s_stk->fork_mutex[free->l_forkid]);
	pthread_mutex_unlock(&free->s_stk->fork_mutex[free->r_forkid]);
	free->count_eat++ ;
}

void	*start(void *stk)
{
	t_list	*free;

	free = (t_list *)stk;
	free->last_eat = gettime();
	if (free->id % 2)
		usleep(1000);
	while (free->s_stk->dead == 0)
	{
		starteating(free);
		if (!eatcheck(free))
			break ;
		if (free->s_stk->dead == 1)
			break ;
		printthreadm(free->id, RED"is sleeping\n"RESET, free->s_stk);
		passtime(free->s_stk->time_to_sleep, free);
		printthreadm(free->id, CYAN"is thinking\n"RESET, free->s_stk);
	}
	return (NULL);
}

int	createthread(t_philos *stk, int i, uint64_t time)
{
	pthread_t	id;

	while (i < stk->number_of_philo)
	{
		pthread_create(&stk->link[i].th_id, NULL, &start, &stk->link[i]);
		i++;
	}
	pthread_create(&id, NULL, &deadcheck, stk);
	i = -1;
	while (++i < stk->number_of_philo)
	{
		pthread_join(stk->link[i].th_id, NULL);
		pthread_detach(stk->link[i].th_id);
	}
	pthread_join(id, NULL);
	pthread_detach(id);
	while (i < stk->number_of_philo)
		pthread_mutex_destroy(&stk->fork_mutex[--i]);
	pthread_mutex_destroy(&stk->random);
	return (0);
}
