/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkaya <sakkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:31:26 by sakkaya           #+#    #+#             */
/*   Updated: 2023/07/26 03:58:21 by sakkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_philos *stk, int ac)
{
	stk->link = malloc(sizeof(t_list) * stk->number_of_philo);
	if (!stk->link)
		return (0);
	while (ac < stk->number_of_philo)
	{
		stk->link[ac].id = ac;
		stk->link[ac].l_forkid = ac;
		stk->link[ac].r_forkid = (ac + 1) % stk->number_of_philo;
		stk->link[ac].count_eat = 0;
		stk->link[ac].s_stk = stk;
		stk->link[ac].last_eat = gettime();
		ac++;
	}
	return (1);
}

int	init_arguments(int ac, char **av, t_philos *stk)
{
	if (!line_25(av))
		return (0);
	stk->number_of_philo = ft_atoi(av[1]);
	stk->time_to_die = ft_atoi(av[2]);
	stk->time_to_eat = ft_atoi(av[3]);
	stk->time_to_sleep = ft_atoi(av[4]);
	stk->start_time = gettime();
	stk->check = -1;
	if (ac == 6) 
		stk->must_eat = ft_atoi(av[5]);
	else
		stk->must_eat = -1;
	stk->dead = 0;
	stk->fork_mutex = malloc(sizeof(pthread_mutex_t) * stk->number_of_philo);
	if (!stk->fork_mutex)
		return (0);
	ac = 0;
	pthread_mutex_init(&stk->random, NULL); 
	while (stk->number_of_philo > ac)
		pthread_mutex_init(&stk->fork_mutex[ac++], NULL);
	if (!init_philos(stk, 0))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_philos		*stk;
	uint64_t		time;

	if (ac != 5 && ac != 6)
	{
		printf(RED"More or not enough arguments."RESET);
		return (0);
	}
	if (!checkargs(av, 1))
		return (0);
	stk = malloc(sizeof(t_philos));
	if (!init_arguments(ac, av, stk))
	{
		freesth (stk->link, stk);
		return (0);
	}
	if (!createthread(stk, 0, time))
	{
		freesth (stk->link, stk);
		return (0);
	}
	freesth (stk->link, stk);
}
