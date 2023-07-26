/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:09:00 by kdemirci          #+#    #+#             */
/*   Updated: 2023/07/26 01:15:15 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*init_data(int ac, char **av)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	tmp->num_philo = ft_atoi(av[1]);
	tmp->num_fork = tmp->num_philo;
	if (tmp->num_philo == 1)
	{
		printf("a philosopher has died\n");
		exit(1);
	}
	tmp->t_die = ft_atoi(av[2]);
	tmp->t_eat = ft_atoi(av[3]);
	tmp->t_sleep = ft_atoi(av[4]);
	tmp->must_eat = 0;
	if (ac == 6)
		tmp->must_eat = ft_atoi(av[5]);
	tmp->is_died = 0;
	tmp->ate = 0;
	return (tmp);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo	*philo;

	philo = init_data(ac, av);
	philo->philo_id = (int *)malloc(sizeof(int) * philo->num_fork);
	sem_unlink("/print_lock");
	sem_unlink("/fork_lock");
	philo->print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
	philo->fork_lock = sem_open("/fork_lock", O_CREAT, 0644, philo->num_fork);
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\n");
		exit(-1);
	}
	philo = init_philo(ac, av);
	check_args(philo);
	philo->start_time = get_time();
	while (i < philo->num_philo)
	{
		philo->philo_id[i] = fork();
		if (philo->philo_id[i] == 0)
		{
			philo->index = i + 1;
			philo->last_meal = get_time();
			start_dinner(philo);
		}
		i++;
	}
	fin_dinner(&philo);
	return (0);
}
